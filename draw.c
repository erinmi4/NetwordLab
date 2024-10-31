/*************************************************************************
	> File Name: color.c
	> Author: csgec
	> Mail: 12345678@qq.com
	> Created Time: 2024年10月28日 星期一 16时35分10秒
 ************************************************************************/
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "draw.h"

// 坐标范围 480 * 800
#define WIDTH 800
#define HEIGHT 480

// plcd使用全局变量，没有封装
int *plcd = NULL;
int size = WIDTH * HEIGHT;

/* 根据坐标，获得对应的位置 */
int coordinate(int x, int y) {
    return x + y * WIDTH;
}

/* 判断坐标是否合理 */
int valid(int x, int y) {
    return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

/* 在某一点，将其绘成对应的颜色 */
void draw_point(int x, int y, int color) {
    if (valid(x, y)) {
        *(plcd + coordinate(x, y)) = color;
    }
}

/* 获取较小值 */
int min(int a, int b) {
    return (a < b) ? a : b;
}

/* 获取较大值 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* 将整个屏幕绘制为同一个颜色 */
void lcd_clear(int color) {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; y++) {
            draw_point(x, y, color);
        }
    }
}

/* 判断点是否在圆内 */
int in_circle(int x0, int y0, int x1, int y1, int radius) {
    int x_dis = (x1 - x0);
    int y_dis = (y1 - y0);
    return (x_dis * x_dis + y_dis * y_dis <= radius * radius);
}

/* 初始化屏幕的文件描述符 */
int init_lcd() {
    int fd = open("/dev/fb0", O_RDWR);
    if (fd == -1) {
        perror("open framebuffer device");
        exit(EXIT_FAILURE);
    }
    plcd = mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (plcd == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return fd;
}

/* 画一个圆 */
void draw_circle(int x1, int y1, int radius, int color) {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; y++) {
            if (in_circle(x1, y1, x, y, radius)) {
                draw_point(x, y, color);
            } else {
                draw_point(x, y, 0x000000); // 黑色
            }
        }
    }
}

/* 关闭文件描述符 */
void close_lcd(int fd) {
    munmap(plcd, size * sizeof(int));
    close(fd);
}


/*
    函数:
        lcd_draw_word 显示一个字符
    参数列表:
        x,y:在哪个位置开始显示一个字符
        w:字符的宽,这个宽度不是/8之后的值
        h:字符的高
        data:字符的取模数组
        color:要显示的是啥颜色
*/
void lcd_draw_word(int x,int y,int w,int h,unsigned char data[],int color)
{
    int i,j;//i用来遍历我们这个数组的所有元素,j是用来遍历每一个元素的每一个bit位
    //遍历数组
    for(i = 0;i < w*h/8;i++)
    {
        //遍历这个数组元素的每一个bit位
        for(j = 7;j >= 0;j--)
        {
            //只要这个bit位为1上色,为0不需要管
            if(data[i] >> j & 1)
            {
                //开发板上的一个像素点就是对应了取模数据的一个bit位
                int x0 = x + i%(w/8)*8 + 7-j;
                /*
                    i%(w/8):求出这个元素是在这行的第几个
                    *8:每一个元素都有8个bit位
                    7-j:从高位开始解析数据
                */
                int y0 = y + i/(w/8);

                draw_point(x0,y0,color);
            }
        }
    }
}