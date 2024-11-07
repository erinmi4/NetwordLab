#include "main.h"

// 向管道文件写入命令
int Send_Cmd(char *cmd)
{
    write(fd_fifo, cmd, strlen(cmd));
    return 0;
}

// 旧版视频播放
/*
    输入：视频文件路径，视频宽度，高度
    输出：播放视频
    返回值：成功返回0，失败返回-1
*/
int VideoPlay_old(char videopath[], int width, int height)
{   
    show_1152000bmp("./picture/video_play.bmp", p_lcd);
    system("killall -9 mplayer"); // 停止其他视频播放
    char Video[255];
    sprintf(Video, "mplayer -slave -quiet -input file=/fifo -geometry 0:0 -zoom -x %d -y %d %s &", width, height, videopath);
    system(Video);

    // 视频操作
    int posx, posy;
    int choice;
    int VideoMode = 1; // 1表示播放状态，0表示暂停状态
    do {
        int nTouch = project_touch(&posx, &posy);
        choice = (nTouch == 0) ? 1 : (nTouch == 4 ? 0 : -1); // 1-暂停/继续, 0-退出

        switch (choice) {
            case 0:
                system("killall -SIGKILL mplayer"); // 退出视频
                break;
            case 1:
                if (VideoMode == 1) {
                    system("killall -SIGSTOP mplayer"); // 暂停视频
                    VideoMode = 0;
                } else {
                    system("killall -SIGCONT mplayer"); // 继续播放
                    VideoMode = 1;
                }
                break;
            default:
                printf("Error!\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

// 新版视频播放
/*
    输入：视频文件路径
    输出：播放视频
    返回值：成功返回0
*/
int VideoPlay(char videopath[])
{   
    // show_1152000bmp("./picture/video_play.bmp", p_lcd);
    system("killall -9 mplayer"); // 停止其他视频播放
    char Video[255];
    sprintf(Video, "mplayer %s &", videopath);
    system(Video);

    // 视频操作
    int posx, posy;
    int choice;
    int VideoMode = 1; // 1表示播放状态，0表示暂停状态
    do {
        int nTouch = project_touch(&posx, &posy);
        choice = (nTouch == 0) ? 1 : (nTouch == 4 ? 0 : -1); // 1-暂停/继续, 0-退出

        switch (choice) {
            case 0:
                system("killall -SIGKILL mplayer"); // 退出视频
                break;
            case 1:
                if (VideoMode == 1) {
                    system("killall -SIGSTOP mplayer"); // 暂停视频
                    VideoMode = 0;
                } else {
                    system("killall -SIGCONT mplayer"); // 继续播放
                    VideoMode = 1;
                }
                break;
            default:
                printf("Error!\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
