//
// Created by 25115 on 2024/10/29.
//
#include <sys/mman.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "touch.h"
#include <linux/input.h>

//坐标范围 600 * 1024
//注意每次打印要添加 换行符

//根据开始坐标和结束坐标，判断方向
void detect_direction(int first_x, int first_y, int end_x, int end_y){
    if(abs(end_x - first_x) > abs(end_y - first_y)) {
        //说明在x轴相比于y上位移更大，也就是左右滑动
        if(end_x > first_x) {
            //右滑
            printf("Right\n");
            return;
        }
        else {
            //左滑
            printf("Left\n");
            return;
        }
    }
    else{
        if(end_y > first_y) {
            //上滑
            printf("Upward\n");
            return;
        }
        else {
            //下滑
            printf("Downward\n");
            return;
        }
    }
}

int Init_touch() {
        //获得文件描述符
    int touch_fd = open("/dev/input/event0",O_RDWR);
    if(touch_fd == -1){
        printf("open touch event file error \n");
        exit(0);
    }
    return touch_fd;
}

void touch_close(int touch_fd){
    close(touch_fd);
}

void Get_abs(int touch_fd){
    struct input_event ev;
    //初始赋值
    int x = -1,y = -1;
    while (1) {
        read(touch_fd,&ev, sizeof(ev));
        //获取x轴的坐标
        if(ev.type == EV_ABS && ev.code == ABS_X){
            //printf("%d %s\n",__LINE__,__FUNCTION__);
                        x = ev.value;
        }
        if(ev.type == EV_ABS && ev.code == ABS_Y){
            //printf("%d %s\n",__LINE__,__FUNCTION__);
                        y = ev.value;
        }
        //打印坐标值
        printf("(%d,%d)\n",x,y);
    }
}

/*获取滑动的方向
 * 注意每次更新 x , y作为标志位的结果
 * */
void Get_touch_direction(int touch_fd) {
    struct input_event ev;
    //初始赋值,作为标志位判断是否是第一次更改
    int x = -1, y = -1;
    //记录第一次的值
    int first_x, first_y;
    //记录每一次划过的值，最后保留的就是结束的值
    int recode_x, recode_y;


    while (1) {
        read(touch_fd,&ev, sizeof(ev));
        //获取x轴的坐标
        if(ev.type == EV_ABS && ev.code == ABS_X){
            recode_x = ev.value;
            //将初次获取的x值
            if(x == -1){
                //修改标志位
                x = 0;
                first_x = ev.value;
            }
            continue;
        }
        if(ev.type == EV_ABS && ev.code == ABS_Y){
            recode_y = ev.value;
                //获取初次获取的x值
            if(y == -1){
                y = 0;
                first_y = ev.value;
            }
            continue;
        }
        //判断手是否脱离屏幕
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) {
            printf("%d %d %d %d \n",first_x,first_y,recode_x,recode_y);
            //@problem：只能打印left和down
            detect_direction(first_x,first_y,recode_x,recode_y);
            x = -1;
            y = -1;
        }
    }
}