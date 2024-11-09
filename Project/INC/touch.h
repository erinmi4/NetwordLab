//
// Created by 25115 on 2024/11/7.
//

#ifndef PROJECT_TOUCH_H
#define PROJECT_TOUCH_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <strings.h>

/*--------------------------自定义宏定义--------------------------*/
#define TOUCH_PATH  "/dev/input/event0" //宏定义触摸屏的路径
//宏定义操作方向
#define TOUCH_INIT      0//定义方向初始化的值用于取消其所有的方向值
#define TOUCH_NOMV      1//定义单点的方向值
#define TOUCH_RIGHT     2//定义向右的方向值
#define TOUCH_LEFT      3//定义向左的方向值
#define TOUCH_UP        4//定义向上的方向值
#define TOUCH_DOWN      5//定义向下的方向值

#define TOUCH_X_SCALE  (800.0f / 1024.0f)
#define TOUCH_Y_SCALE  (480.0f / 600.0f)


/*-------------------定义结构体---------------*/
struct Touch_val
{
    int ts_fd;//触摸屏的文件描述符
    int x;  //读取触摸屏X轴，作为全局变量使用
    int y;  //读取触摸屏Y轴，作为全局变量使用
    int move_dir;//移动方向
    int Touch_leave;//松手的标志
};

/*-------------------定义函数-----------------*/
//初始化触摸屏获得触摸屏文件描述符
void Touch_Init(struct Touch_val *Touch);
//输入触摸屏结构体指针获取触摸屏是进行了滑动操作还是单击操作,在结构体中返回操作方向
void Touch_Scan(struct Touch_val *Touch);
//作为触摸屏线程的执行函数
void* Touch_SCAN(void* Touch);

#endif //PROJECT_TOUCH_H
