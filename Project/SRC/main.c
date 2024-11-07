//
// Created by 25115 on 2024/11/7.
//

#include "../INC/main.h"


int main() {
    /*------------------------LCD初始化---------------------*/
    struct Lcd_Init *LCD = calloc(1,sizeof(struct Lcd_Init));//定义LCD结构体指针并为其配置内存空间
    LCD_Init(LCD);//获取打开LCD文件的文件描述符，并为LCD显示的像素点配置内存映射


    /*------------------------触摸初始化---------------------*/
    struct Touch_val *Touch = calloc(1,sizeof(struct Touch_val));//定义触摸屏结构体指针并为其配置内存空间touch
    Touch_Init(Touch);//获取打开触摸屏文件的文件描述符

    /*------------------------定义线程相关---------------------*/
    pthread_t Touch_pid;//定义一个用于扫描触摸屏的线程
    pthread_create(&Touch_pid,NULL,Touch_SCAN,(void *)Touch);//配置扫描触摸屏线程


}