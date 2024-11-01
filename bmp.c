//
// Created by 25115 on 2024/10/30.
//

#include "bmp.h"
#include <sys/mman.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "draw.h"
#include <stdlib.h>
#include <linux/input.h>
#include "touch.h"

/*
 * 获取颜色数组，对于不足的部分使用赖子数进行补足
 * 返回一个指针，这个指针指向所在行，并且包含该行的内容
 * */
void Bmp_show(char* path){

        //获得文件描述符
    int bmp_fd = open(path, O_RDWR);
    if (bmp_fd == -1) {
        printf("open txt file error \n");
        exit(0);
    }

    int width;
    lseek(bmp_fd,0x12,SEEK_SET);
    read(bmp_fd,&width,4);

    int heigth;
    lseek(bmp_fd,0x16,SEEK_SET);
    read(bmp_fd,&heigth,4);

    short depth;
    lseek(bmp_fd,0x1c,SEEK_SET);
    read(bmp_fd,&depth,2);


    int line_valid_bytes;//每一行的有效字节数
    int line_bytes;//每一行的实际字节数 = 有效字节数 + 赖子数
    int total_bytes;//总字节数
    int laizi;//赖子数

    line_valid_bytes = abs(width) * depth / 8;

    //判断是否需要填充赖子
    if(line_valid_bytes % 4)
    {
        laizi = 4 - line_valid_bytes%4;
    }
    line_bytes = line_valid_bytes + laizi;
    total_bytes = line_bytes * abs(heigth);

    //一口气读取所有的像素数据
    unsigned char *piexls = malloc(total_bytes);//用数组也可以
    //@problem没有补足分配空间失败的情况

    lseek(bmp_fd,54,SEEK_SET);
    read(bmp_fd,piexls,total_bytes);

    //处理像素数组的数据
    unsigned char a,r,g,b;//每次保存每个像素点的颜色分量值的每个字节
    int color;//颜色分量,需要处理数据得到
    int i = 0;//帮助遍历像素数组
    int x,y;//遍历LCD屏幕
    for(y = 0;y < abs(heigth);y++)//遍历所有行
    {
        for(x = 0;x < abs(width);x++)//遍历当前这一行的所有列
        {
            b = piexls[i++];
            g = piexls[i++];
            r = piexls[i++];
            //在获取色深之前,需要判断是否有色深这一个字节的变量
            if(depth == 32)
            {
                a = piexls[i++];
            }
            else
            {
                a = 0;
            }
            //合成颜色,显示到对应的位置上
            color = a<<24|r<<16|g<<8|b;

            draw_point(width>0? x:abs(width)-1-x,heigth>0? abs(heigth)-1-y:y,color);
        }
        //每次遍历完一行之后,跳过赖子数
        i = i + laizi;
    }
    free(piexls);
    close(bmp_fd);
}

// 显示BMP图片到LCD,并且存在偏移量x0 y0
void lcd_show_bmp(int x0, int y0, char *path) {
    //清屏
    //lcd_clear(BLACK_COLOR);

    // 打开BMP文件
    int bmp_fd = open(path, O_RDWR);
    if (bmp_fd == -1) {
        printf("Error opening BMP file: %s\n", path);
        return;
    }

    // 获取图片宽度
    int width;
    lseek(bmp_fd, 0x12, SEEK_SET);
    read(bmp_fd, &width, 4);

    // 获取图片高度
    int height;
    lseek(bmp_fd, 0x16, SEEK_SET);
    read(bmp_fd, &height, 4);

    // 获取色深
    short depth;
    lseek(bmp_fd, 0x1c, SEEK_SET);
    read(bmp_fd, &depth, 2);

    // 计算每行有效字节数和填充字节数
    int line_valid_bytes = abs(width) * depth / 8;
    int laizi = (4 - (line_valid_bytes % 4)) % 4; // 赖子数
    int line_bytes = line_valid_bytes + laizi; // 每行实际字节数

    // 分配内存并读取像素数据
    unsigned char *pixels = malloc(line_bytes * abs(height));
    if (!pixels) {
        printf("Error allocating memory for pixel data\n");
        close(bmp_fd);
        return;
    }

    lseek(bmp_fd, 54, SEEK_SET);
    read(bmp_fd, pixels, line_bytes * abs(height));

    // 处理像素数据并绘制到LCD
    int i = 0; // 像素数据索引
    for (int y = 0; y < abs(height); y++) {
        for (int x = 0; x < abs(width); x++) {
            unsigned char b = pixels[i++];
            unsigned char g = pixels[i++];
            unsigned char r = pixels[i++];
            unsigned char a = (depth == 32) ? pixels[i++] : 0; // 处理透明度

            // 合成颜色
            int color = (a << 24) | (r << 16) | (g << 8) | b;

            // 计算LCD坐标
            int lcd_x = x0 + (width > 0 ? x : abs(width) - 1 - x);
            int lcd_y = y0 + (height > 0 ? (abs(height) - 1 - y) : y);

            // 绘制点
            draw_point(lcd_x, lcd_y, color);
        }
        // 跳过赖子数
        i += laizi;
    }

    // 清理资源
    free(pixels);
    close(bmp_fd);
}