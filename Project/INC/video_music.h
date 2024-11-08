//
// Created by 25115 on 2024/11/8.
//

#ifndef PROJECT_VIDEO_MUSIC_H
#define PROJECT_VIDEO_MUSIC_H

#include "main.h"

/*-------------------宏定义---------------*/
//关于管道文件路径的宏定义
#define FIFOPATH_MP3    "/tmp/MP3"  //MP3的管道文件
#define FIFOPATH_AVI    "/tmp/AVI"  //AVI的管道文件
//关于MPLAYER的相关控制命令
#define MPLAYER_TIPS1   "mplayer -quiet -slave -input file="//MP3的MPLAYER开启前语
#define MPLAYER_TIPS2   "mplayer -quiet -slave -zoom -x 800 -y 400 -input file="//AVI的MPLAYER开启前语
#define MPLAYER_INIT_V  " -af volume=-30 "//设置MPLAYER开启的初始音量
/*-------------------定义结构体---------------*/
//声明已经定义过的结构体
struct Lcd_Init;
struct Touch_val;
struct Filedir;

//初始化创建对应路径下的管道文件
void Fifo_Init(char * FifoPath);
//对目标管道文件进行写入操作
void WR_Fifo(char * FifoPath,char * command);
//AVI线程执行函数
void* AVI_PLAY(void* AVIDir);
//AVI播放功能函数
void AVI_PlayStart(struct Lcd_Init * LCD,struct Touch_val * Touch,struct Filedir * AVIFile,struct Filedir * SystemFile,
                    pthread_t AVI_pid,int * Control_Num);
//MP3线程执行函数
void* MP3_PLAY(void* MP3Dir);
//MP3播放功能函数
void MP3_PlayStart(struct Lcd_Init * LCD,struct Touch_val * Touch,struct Filedir * MP3File,struct Filedir * SystemFile,
                    pthread_t MP3_pid,int * Control_Num);

/*
 * 为什么要使用管道
 1. 控制命令的传递：通过管道，
 主程序可以向播放器进程（如mplayer）发送控制命令，
 如播放、暂停、快进、快退、调整音量等。这些命令被写入管道，然后由播放器进程读取并执行。
 2. 解耦控制逻辑和播放逻辑：使用管道可以将控制逻辑（如触摸屏输入处理）与播放逻辑（如视频/音频播放）分离开来。
 这样，控制逻辑可以独立于播放逻辑进行开发和测试，提高了代码的模块化和可维护性。
 3. 线程间的同步：在多线程环境中，管道可以用于同步不同线程的行为。
 例如，当一个线程需要等待另一个线程完成特定操作（如视频播放结束）时，可以通过管道发送信号来实现同步。*/
#endif //PROJECT_VIDEO_MUSIC_H
