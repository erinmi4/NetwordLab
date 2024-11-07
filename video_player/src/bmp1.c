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
        perror("��ͼƬ�ļ�ʧ��");
        return -1;
    }

    int width, height;
    short depth;
    
    // ��ȡͼƬ�Ŀ�Ⱥ͸߶�
    if (lseek(fd, 0x12, SEEK_SET) == -1 || read(fd, &width, 4) != 4 || read(fd, &height, 4) != 4)
    {
        perror("��ȡͼƬ��Ⱥ͸߶�ʧ��");
        close(fd);
        return -1;
    }

    // ��ȡͼƬ��ɫ��
    if (lseek(fd, 0x1c, SEEK_SET) == -1 || read(fd, &depth, 2) != 2)
    {
        perror("��ȡͼƬɫ��ʧ��");
        close(fd);
        return -1;
    }
    printf("���: %d, �߶�: %d, ɫ��: %d\n", width, height, depth);

    int padding = (4 - (width * depth / 8) % 4) % 4;
    size_t lineSize = width * depth / 8 + padding;
    unsigned char colorBuffer[height * lineSize];
    
    // ������ɫ������������ɫ����
    unsigned char color_a = 0, color_r, color_g, color_b;
    unsigned int color;
    unsigned char *pixelPtr = colorBuffer;

    // ��λ���������ݵ���ʼλ��
    if (lseek(fd, 0x36, SEEK_SET) == -1 || read(fd, colorBuffer, height * lineSize) != height * lineSize)
    {
        perror("��ȡ��������ʧ��");
        close(fd);
        return -1;
    }
    close(fd);

    // ��ʾͼƬ����
    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            color_b = *pixelPtr++; // B ��ɫ����
            color_g = *pixelPtr++;
            color_r = *pixelPtr++;
            if (depth == 32)
            {
                color_a = *pixelPtr++;
            }
            color = (color_a << 24) | (color_r << 16) | (color_g << 8) | color_b; // ARGB ��ɫֵ
            Display(color, j, i);
        }
        pixelPtr += padding; // ����ÿ��ĩβ������ֽ�
    }

    return 0;
}

void Dis_pan() // ��������
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i % 40 == 0 || j % 40 == 0)
            {
                Display(0x000000, j, i); // ����������ɫΪ��ɫ
            }
            else
            {
                Display(0xFFFFFF, j, i); // ���̸���ɫΪ��ɫ
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
                Display(color, j, i); // ����Բ������
            }
        }
    }
}*/
