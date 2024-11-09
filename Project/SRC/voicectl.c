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
        // 1.调用arecord来录一段音频
        printf("请在3秒后开始录音...\n");
        system(REC_CMD); // 执行录音命令

        // 2.将录制好的PCM音频发送给语音识别引擎
        send_pcm(sockfd_tcp, PCM_FILE);

        // 3.等待对方回送识别结果（字符串ID）
        xmlChar* id = wait4id(sockfd_tcp);
        if (id == NULL)
        {
            continue;
        }
        
        id_num = atoi((char*)id);
        switch (id_num)
        {
            case 9:
                Control_Num = MUSIC_PLAY;
                printf("Enter mp3 play interface\n");
                break;
            case 10:
                Control_Num = ENTER_KUGOU;
                printf("Enter video play interface\n");
                break;
            case 2:
                // 暂停
				Control_Num == MUSIC_STOP_CONT
                break;
			case 13:
				//播放
				
				break;	
            case 3:
                // 上一曲
                break;
            case 4:
                // 下一曲
                break;
            case 11:
                // 上一个视频
                break;
            case 12:
                // 下一个视频
                break;
            case 999:
                printf("bye！\n");
                break;
            default:
                printf("Unknow command\n");
                break;
        }

        printf("receive: %d\n", id_num);
        // 通过UDP发送数据给接收端, 接收端收到数据id后再决定执行什么功能
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