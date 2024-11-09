#include "common.h"
#include "voicectl.h"
#include "main.h"

extern int Control_Num;

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

/* 语音识别控制函数 
参数：ubuntu的ip地址
返回：0-识别成功，1-识别失败
*/
int voicectl(char *ip)
{
	signal(SIGPIPE, catch);
	// 初始化TCP客户端套接字，用于连接到语音识别服务器(即ubuntu)
	int sockfd_tcp = init_tcp_socket(ip);
	// 初始化本地UDP套接字
	int sockfd_udp = init_udp_socket();

	int id_num = -1; // 识别后的指令id
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
		if (id_num == 9)
		{
			//进入播放音乐界面
			Control_Num = MUSIC_PLAY;
			printf("MUSIC_PLAY via voice detect\n");
		}
		if (id_num == 10)
		{
			//进入播放视频界面
			Control_Num = ENTER_KUGOU;
			printf("Video play via voice detect\n");
		}
		
		if (id_num == 999)
		{
			printf("bye-bye!\n");

		}
		printf("recv id: %d \n", id_num);
		// udp发送数据给接收端, 接收端收到数据id后，再决定执行什么功能
		send_id(sockfd_udp, id_num);
		
	}

	return 0;
}

/*
 * 线程执行函数
 * 作  用  ：作为触摸屏线程的执行函数，持续调用voicectl进行语音识别
 * 输入参数：语音识别服务器的IP地址
 */
void* Voicectl_thread(char* ip) {
    while (1) {
        voicectl(ip); // 使用传入的ip参数，持续进行语音识别
    }
}