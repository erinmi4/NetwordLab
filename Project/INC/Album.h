//
// Created by 25115 on 2024/11/7.
//

#ifndef PROJECT_ALBUM_H
#define PROJECT_ALBUM_H
#include "main.h" // 这是依附性功能，不再特定引入额外头文件

/*------------------- 定义结构体 ---------------*/

// 声明已定义的结构体
struct Lcd_Init;
struct Touch_val;
struct Filedir;

// 自定义结构体，用于自动播放
struct AUTO_ON_OFF
{
    int FileNum;  // 记录文件数量
    int *count;   // 记录当前播放的图片编号
};

// 定义启动动画的存储路径
#define START_URL "/IOT/lab/Start/"

/*------------------- 自定义函数 ---------------*/
// 定义相册功能
void Album_Start(struct Touch_val *Touch, struct Lcd_Init *LCD, struct Filedir *File_Photo,
                 struct Filedir *File_System, int *count, int *Control_Num);
// 定义自动播放时计数的线程
void *Auto_Num(void *arg);
// 定义用于开机启动动画的功能
void Start_System(struct Lcd_Init *LCD);
void Wait_For_Touch_Release(struct Touch_val *Touch, int *Control_Num);
void Clear_Touch_States(struct Touch_val *Touch);
#endif //PROJECT_ALBUM_H
