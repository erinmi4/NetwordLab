#include "main.h"

int project_touch(int *th_x, int *th_y)
{
    /*
        功能：获取屏幕点击的坐标
        输入：int指针 th_x 和 th_y，用于存放点击坐标
        输出：异常-1, 点击0，向右移动1，向左移动2, 向下移动3, 向上移动4
        注意：开发板驱动可能有误，可能需对触摸点坐标做比例缩放
    */

    int old_x = 0, old_y = 0;

    while (1)
    {
        read(fd_touch, &buf, sizeof(buf));

        // 处理X坐标
        if (buf.type == EV_ABS && buf.code == ABS_X) 
        {
            *th_x = buf.value * 800 / 1024;//触摸坐标和屏幕坐标比例缩放

        }
        
        // 处理Y坐标
        if (buf.type == EV_ABS && buf.code == ABS_Y) 
        {
            *th_y = buf.value * 480 / 600;//触摸坐标和屏幕坐标比例缩放
        }

        // 检测触摸开始
        if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 1) 
        {
            old_x = *th_x;
            old_y = *th_y;
        }

        // 检测触摸结束并计算移动方向
        if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0) 
        {
            if (old_x < *th_x && (*th_x - old_x >= 50)) return 1; // 向右移动
            if (old_x > *th_x && (old_x - *th_x >= 50)) return 2; // 向左移动
            if (old_y < *th_y && (*th_y - old_y >= 50)) return 3; // 向下移动
            if (old_y > *th_y && (old_y - *th_y >= 50)) return 4; // 向上移动
            break;
        }
    }
    return 0;
}
