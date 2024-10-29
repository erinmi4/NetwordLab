/*************************************************************************
	> File Name: color.c
	> Author: csgec
	> Mail: 12345678@qq.com
	> Created Time: 2024年10月28日 星期一 16时35分10秒
 ************************************************************************/
#include <sys/mman.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "draw.h"
#include <stdlib.h>

int *plcd = NULL;
int size = 480 * 800;
int fd;//文件描述符

/*根据坐标，获得对应的位置*/
int coordinate(int x, int y) {
    return x + y * 800;
}

/*判断坐标是否合理*/
int valid(int x, int y) {
    if(x >= 0 && x < 800 && y >= 0 && y < 480){
        return 1;
    }
    return 0;
}

/*在某一点，将其绘成对应的颜色*/
void draw_point(int x, int y, int color) {
    int zuobiao = coordinate(x,y);
    if(x >= 0 && x < 800 && y >= 0 && y < 480){
        *(plcd + zuobiao) = color;
    }
}
//获取较小值
int min(int a, int b) {
    if (a - b <= 0) {
        return a;
    }
    return b;
}
//获取较大值
int max(int a, int b) {
    if (a - b >= 0) {
        return a;
    }
    return b;
}

void lcd_clear() {
    for (int x = 0; x < X_LENGTH; ++x) {
        for (int y = 0; y < Y_LENGTH; y++) {
                draw_point(x,y,0x000000);
        }
    }
}

//圆心x0和圆上x1是否满足条件,在园内
int in_circle(int x0 , int y0, int x1 , int y1,int radius){
    int x_dis = (x1 - x0);
    int y_dis = (y1 - y0);
    if (x_dis * x_dis + y_dis * y_dis <= radius * radius) {
        return 1;
    }
    return  0;
}

void init_lcd() {
    //获得文件描述符
    fd = open("/dev/fb0",O_RDWR);
	if(fd == -1){
        printf("open txt file error \n");
        exit(0);
    }
    //内存映射
    plcd = mmap(NULL,size * sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
}

void draw_circle(int x1 , int y1,int radius,int color){
    //上色
    for (int x = 0; x < X_LENGTH; ++x) {
        for (int y = 0; y < Y_LENGTH; y++) {
            if (in_circle(x1,y1,x,y,radius) == 1){
                draw_point(x,y,color);
            }
            else{
                draw_point(x,y,0x000000);
            }
        }
    }
}

void close_lcd(){
    //解除映射
    int res = munmap(plcd, size * sizeof(int));
    //关闭文件描述符
    close(fd);
}



////绘制一条直线
//void draw_line(int x1, int y1, int x2, int y2, int color) {
//
//    int GPS1 = coordinate(x1, y1);
//    int GPS2 = coordinate(x2, y2);
//
//    //如果是一条横线
//    if (y1 == y2) {
//        for (int i = min(x1,x2); i < max(x1,x2); ++i) {
//            draw_point()
//        }
//    }
//    else if(x1 == x2) {
//        //绘制一条竖线
//    }
//    else {
//        //绘制一条斜线
//    }
//
//}