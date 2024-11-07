#include "bmp.h"
#include "ev.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int Dis_pic(char *pic)
{
    int fd = open(pic, O_RDONLY);
    if (fd == -1)
    {
        perror("打开图片文件失败");
        return -1;
    }

    int width, height;
    short depth;
    
    // 读取图片的宽度和高度
    if (lseek(fd, 0x12, SEEK_SET) == -1 || read(fd, &width, 4) != 4 || read(fd, &height, 4) != 4)
    {
        perror("读取图片宽度和高度失败");
        close(fd);
        return -1;
    }

    // 读取图片的色深
    if (lseek(fd, 0x1c, SEEK_SET) == -1 || read(fd, &depth, 2) != 2)
    {
        perror("读取图片色深失败");
        close(fd);
        return -1;
    }
    printf("宽度: %d, 高度: %d, 色深: %d\n", width, height, depth);

    int padding = (4 - (width * depth / 8) % 4) % 4;
    size_t lineSize = width * depth / 8 + padding;
    unsigned char colorBuffer[height * lineSize];
    
    // 设置颜色分量和像素颜色变量
    unsigned char color_a = 0, color_r, color_g, color_b;
    unsigned int color;
    unsigned char *pixelPtr = colorBuffer;

    // 定位到像素数据的起始位置
    if (lseek(fd, 0x36, SEEK_SET) == -1 || read(fd, colorBuffer, height * lineSize) != height * lineSize)
    {
        perror("读取像素数据失败");
        close(fd);
        return -1;
    }
    close(fd);

    // 显示图片像素
    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            color_b = *pixelPtr++; // B 颜色分量
            color_g = *pixelPtr++;
            color_r = *pixelPtr++;
            if (depth == 32)
            {
                color_a = *pixelPtr++;
            }
            color = (color_a << 24) | (color_r << 16) | (color_g << 8) | color_b; // ARGB 颜色值
            Display(color, j, i);
        }
        pixelPtr += padding; // 跳过每行末尾的填充字节
    }

    return 0;
}

void Dis_pan() // 绘制棋盘
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i % 40 == 0 || j % 40 == 0)
            {
                Display(0x000000, j, i); // 棋盘线条颜色为黑色
            }
            else
            {
                Display(0xFFFFFF, j, i); // 棋盘格颜色为白色
            }
        }
    }
}

/*void Draw_Ck(int x0, int y0, int color)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if ((j - x0) * (j - x0) + (i - y0) * (i - y0) <= 100)
            {
                Display(color, j, i); // 绘制圆形区域
            }
        }
    }
}*/
