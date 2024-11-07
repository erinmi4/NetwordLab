#include <sys/types.h>          /* See NOTES */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <math.h>
#include "draw.h"
//#include "charlib.h"
#include "touch.h"
#include "bmp.h"
#include "music.h"

//视频列表
char *video_list[] = {
    "/IOT/lab/video/video1.mp4",
    "/IOT/lab/video/video2.mp4",
    "/IOT/lab/video/video3.mp4",
    "/IOT/lab/video/video4.mp4",
    }

//暂停视频播放
void video_stop()
{
	slstem("killall -STOP mplayer");
}

//继续视频播放
void video_continue(){
    system("killall -CONT mplayer");
}

//杀死视频进程
void video_cancel(){
    system("killall -9 mplayer");
}

//启动从模式从坐标(0,0)开始播放宽800高480的视频
void video_play(char *path){
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mplayer -slave -quiet -geometry 0:0 -zoom -x 800 -y 480 %s", path);
    system(cmd);
}


//循环播放视频
void video_loop(char *path){
    // 使用 snprintf 正确拼接命令字符串
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mplayer -fs -loop 0 -slave -quiet -geometry 0:0 -zoom -x 800 -y 480 %s", path);
    // 调用 system 函数执行命令
    system(cmd);
}

//上一个视频,可以通过视频的路径来判断
void video_previous(char *path){
    //杀死当前进程
    video_cancel();
    //再上一首
    video_play(path);
}