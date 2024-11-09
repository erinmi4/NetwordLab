//
// Created by 25115 on 2024/11/7.
//

#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

/*--------------------------头文件引用--------------------------*/
//系统头文件
#include <sys/types.h>          /* See NOTES */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <math.h>
//#include "charlib.h"
#include "touch.h"
#include <pthread.h>
#include "draw.h"
#include "Album.h"
#include "video_music.h"
#include "Filedir.h"
#include "System.h"
#include "voicectl.h"
 #include <sys/mman.h>
 #include <linux/input.h>
 #include"game.h"

 /*--------------------------自定义宏定义--------------------------*/
//需要目录检索的目录
#define SYSTEM_PHOTO_DIR    "/IOT/lab/Picture/"    //系统图片文件目录 
#define BMP_PHOTO_DIR       "/IOT/lab/BMP/"   //BMP图片文件目录
#define MP3_DIR             "/IOT/lab/music/"     //MP3文件目录
#define AVI_DIR             "/IOT/lab/AVI/"     //AVI文件目录
#define MP4_DIR             "/IOT/lab/MP4/"
#define GAME_DIR            "/IOT/lab/game/"
/*--------------------------自定义宏定义--------------------------*/

void* AVI_PLAY(void* AVIDir);

#endif //PROJECT_MAIN_H
