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
// #include "charlib.h"
#include "touch.h"
#include "bmp.h"


//播放制定列表下的音频
void music_loop(char *path){
    //在后台列表的音频循环播放 
    system("madplay %s/*.mp3 -r &",path);
}

void music_stop(){
    //暂停音乐的播放 
    system("killall -STOP madplay &");
}

void music_continue(){
    //继续播放音乐 
    system("killall -CONT madplay &");
}

void music_cancel(){
    //退出madplay 
    system("killall -9 madplay");
}