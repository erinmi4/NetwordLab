#include <sys/types.h>
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

// 视频列表
char *video_list[] = {
    "/IOT/lab/video/video1.mp4",
    "/IOT/lab/video/video2.mp4",
    "/IOT/lab/video/video3.mp4",
    "/IOT/lab/video/video4.mp4",
};

// 暂停视频播放
void video_stop() {
    system("killall -STOP mplayer");
    printf("video stop success\n");
}

// 继续视频播放
void video_continue() {
    system("killall -CONT mplayer");
    printf("video continue success\n");
}

// 杀死视频进程
void video_cancel() {
    system("killall -9 mplayer");
    printf("video cancel success\n");
}

// 从 (0, 0) 开始播放宽 800 高 480 的视频
void video_play(char *path) {
    if (path == NULL) {
        printf("Error: Path is NULL\n");
        return;
    }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mplayer -slave -quiet -geometry 0:0 -zoom -x 800 -y 480 %s", path);
    system(cmd);
    printf("video play success\n");
}

// 循环播放视频
void video_loop(char *path) {
    if (path == NULL) {
        printf("Error: Path is NULL\n");
        return;
    }
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mplayer -fs -loop 0 -slave -quiet -geometry 0:0 -zoom -x 800 -y 480 %s", path);
    system(cmd);
    printf("video loop success\n");
}

// 播放上一个视频
void video_previous(char *path) {
    video_cancel(); // 结束当前视频
    for (int i = 1; i < sizeof(video_list) / sizeof(video_list[0]); i++) {
        if (strcmp(video_list[i], path) == 0) {
            video_play(video_list[i - 1]); // 播放上一个视频
            return;
        }
    }
    printf("No previous video found.\n");
}

//播放下一个视频
void video_next(char *path) {
    video_cancel(); // 结束当前视频
    for (int i = 0; i < sizeof(video_list) / sizeof(video_list[0]) - 1; i++) {
        if (strcmp(video_list[i], path) == 0) {
            video_play(video_list[i + 1]); // 播放下一个视频
            return;
        }
    }
    printf("No previous video found.\n");
}