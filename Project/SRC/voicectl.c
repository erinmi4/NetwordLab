#include "common.h"
#include "voicectl.h"
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "draw.h"
#include <stdlib.h>
#include <linux/input.h>
#include "touch.h"
#include "bmp.h"
#include <unistd.h>


//#define REC_CMD  "./arecord -d4 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define REC_CMD  "arecord -d3 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define PCM_FILE "./cmd.pcm"
/* -d：录音时长（duration）
-c：音轨（channels）
-r：采样频率（rate）
-t：封装格式（type）
-f：量化位数（format） */

void catch (int sig)
{
	if (sig == SIGPIPE)
	{
		printf("killed by SIGPIPE\n");
		exit(0);
	}
}

int voicectl(char *ip, int touch_fd)
{
	signal(SIGPIPE, catch);
	// 初始化TCP客户端套接字，用于连接到语音识别服务器(即ubuntu)
	int sockfd_tcp = init_tcp_socket(ip);
	// 初始化本地UDP套接字
	int sockfd_udp = init_udp_socket();

	int id_num = -1; // 识别后的指令id
	int album_flag = 0;//相册标志


	while (1)
	{
		// 1，调用arecord来录一段音频
		printf("please to start REC in 3s...\n");

		// 在程序中执行一条命令  “录音的命令”
		system(REC_CMD);

		// 2，将录制好的PCM音频发送给语音识别引擎
		send_pcm(sockfd_tcp, PCM_FILE);

		// 3，等待对方回送识别结果（字符串ID）
		xmlChar* id = wait4id(sockfd_tcp);
		if (id == NULL)
		{
			continue;
		}
		id_num = atoi((char*)id);
		if (id_num == 999)
		{
			printf("bye-bye!\n");
			return -1;
		}
		if(id_num == 9)
		{
			continue;
		}
        if(id_num == 9){
            printf("Gension start \n");
            album_flag = 1;
            album_show(touch_fd);
        }
        //图片滑动
        if(id_num == 7){
            if(album_flag == 1){
				//可以通过利用线程，同步使用album，并且使得dir为向上，这样可以实现滑动效果。
            }
            else{ continue;}
        }
        if(id_num == 8){
            if(album_flag == 1){

            }
            else{ continue;}
        }

		/*
			10	
		*/
		printf("recv id: %d \n", id_num);
		// udp发送数据给接收端, 接收端收到数据id后，再决定执行什么功能
		send_id(sockfd_udp, id_num);
	}

	return 0;
}
