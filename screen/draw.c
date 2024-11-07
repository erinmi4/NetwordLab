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
#include "charlib.h"

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

        对于data[] 里面的大小为 宽乘以高 除以 8
*/
void lcd_draw_word(int x,int y,int w,int h,unsigned char data[],int color)
{
    int i,j;//i用来遍历我们这个数组的所有元素,j是用来遍历每一个元素的每一个bit位
    //遍历数组
    for(i = 0;i < w*h/8;i++){
        //遍历这个数组元素的每一个bit位
        for(j = 7;j >= 0;j--){
            //只要这个bit位为1上色,为0不需要管
            if(data[i] >> j & 1){
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

void lcd_draw_number(int x,int y,unsigned char data[],int color)
{
    lcd_draw_word(x,y,24,46,data,color);
}

unsigned char* Get_array_num(int i) {
    switch (i) {
        case 0:
            return zero;
        case 1:
            return one;
        case 2:
            return two;
        case 3:
            return three;
        case 4:
            return four;
        case 5:
            return five;
        case 6:
            return six;
        case 7:
            return seven;
        case 8:
            return eight;
        case 9:
            return nine; // 修改拼写错误
        default:
            return NULL; // 返回 NULL
    }
}

/*打印一个数字数组，暂时没有考虑换行*/
void lcd_draw_numarray(int x, int y, int weigh, int heigh, int data[], int color,int arraysize) {
    int cur_x = x;
    int cur_y = y;
    for (int i = 0; i < arraysize; ++i) {
        unsigned char* zifu = Get_array_num(data[i]);
        if (zifu != NULL) { // 检查返回值
            lcd_draw_word(cur_x, cur_y, weigh, heigh, zifu, color);
            cur_x += weigh;
        }
    }
}


/*
    函数:lcd显示一个数字
    参数列表:
        x,y:在哪个位置开始显示一个字符
        w:字符的宽,这个宽度不是/8之后的值
        s:你要显示的数字
        color:要显示的是啥颜色
*/
void lcd_show_num(int x,int y,int w,int h,int s,int color)
{
    //如何把输入的数字变成单个的字符?
    char num[10] = {0};
    sprintf(num,"%d",s);

    //解析num里面的数据进行显示即可
    for(int i = 0;num[i] != 0;i++)
    {
        lcd_draw_word(x,y,w,h,shu[num[i] - '0'],color);
        //每次移动x的坐标
        x = x + w;
    }
}


/*
 * 480 * 800
 * 600 *1024
 * 换算
 * 实现y方向上，从坐标转化为屏幕
 * */
int locate_to_lcd_y(int y){
    float scale_y = (float)480 / 600;
    return (int)(y * scale_y);
}

/*
 * 480 * 800
 * 600 *1024
 * 换算
 * 实现x方向上，从坐标转化为屏幕
 * */
int locate_to_lcd_x(int x){
    float scale_x = (float)800 / 1024;
    return (int)(x * scale_x);
}

/*将控制坐标转化为目标坐标*/
int locate_to_lcd(int srcx,int srcy,int *new_x, int *new_y){
    convert_coordinates(1024,600,800,480,srcx,srcy,new_x,new_y);
}

/* 给出图片左上角的位置，判断坐标是否位于图片内部
 * x0, y0 是图片的左上角坐标
 * x1, y1 是待检查的点的坐标
 * width 和 height 是图片的宽度和高度
 */
int in_rectangle(int x0, int y0, int x1, int y1, int width, int height) {
    if (x1 >= x0 && x1 <= x0 + width && y1 >= y0 && y1 <= y0 + height) {
        return 1;  // 点在图片内部
    }
    return 0;  // 点在图片外部
}

void convert_coordinates(int src_width, int src_height, int dst_width, int dst_height, int x, int y, int *new_x, int *new_y) {
    float scale_x = (float)dst_width / src_width;
    float scale_y = (float)dst_height / src_height;

    *new_x = (int)(x * scale_x);
    *new_y = (int)(y * scale_y);

    // 边界检查和调整
    if (*new_x < 0) {
        *new_x = 0;
    } else if (*new_x >= dst_width) {
        *new_x = dst_width - 1;
    }

    if (*new_y < 0) {
        *new_y = 0;
    } else if (*new_y >= dst_height) {
        *new_y = dst_height - 1;
    }
}


void music_draw(){
    //暂、停、播、放、上、下、一、曲
    // lcd_draw_word(200 + 100, 100, 100, 50,, RED_COLOR);
    // lcd_draw_word(200 + 100, 480 - 100, 100, 50,char_play, RED_COLOR);
    // lcd_draw_word(800 - 200 - 100, 100, 100, 50,pre_song, RED_COLOR);
    // lcd_draw_word(800 - 200 -100, 480 - 100, 100, 50,next_song, RED_COLOR);
}