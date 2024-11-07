//
// Created by 25115 on 2024/11/8.
//

#ifndef PROJECT_FILEDIR_H
#define PROJECT_FILEDIR_H
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

/*--------------------------自定义宏定义--------------------------*/
//函数内值的定义
#define max_FileNum     100 //路径上文件的最多数量值
#define max_DirLong     100 //路径的最大长度
//检索文件类型的定义
#define TYPE_BMP    ".bmp"
#define TYPE_MP3    ".mp3"
#define TYPE_AVI    ".avi"
#define TYPE_JPG    ".jpg"
//为系统文件目录下的文件排序
#define BACKGROUND_NUM      0   //主界面背景图放在第一张
#define MUSIC_PLAY_NUM      1   //音乐播放界面图片放在第二张
#define MUSIC_STOP_NUM      2   //音乐暂停界面图片放在第三张
#define BMPPHOTO_TIP        3   //BMP相册操作提示图放在第四张
#define GUAPHOTO_TIP        4   //刮图操作提示图放在第五张
#define GUABACKGROUND       5   //刮图纯色背景图放在第六张
#define AVI_PLAY_NUM        6   //AVI播放界面图放在第七张
#define AVI_STOP_NUM        7   //AVI播放界面图放在第八张

/*--------------------------自定义宏定义--------------------------*/

/*--------------------------自定义结构体--------------------------*/
struct Filedir
{
    int FileNum;    //记录文件的数量
    char FilePath[max_FileNum][max_DirLong];    //记录文件最多100个文件的路径，且路径长度为100
};
/*--------------------------自定义结构体--------------------------*/

/*-----------------------------       自定义函数      -----------------------------*/
void Read_Dir(struct Filedir * File,char * url,char * type);//读取目录内的文件名
void Read_SystemDir(struct Filedir * File,char * url);//读取系统目录内的文件名并进行排序
/*-----------------------------       自定义函数      -----------------------------*/

#endif //PROJECT_FILEDIR_H
