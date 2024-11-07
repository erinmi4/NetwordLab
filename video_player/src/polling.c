#include "main.h"

// 幻灯片播放
/*
    输入：延时时间（秒）
    输出：幻灯片播放
    返回值：成功返回0，失败返回-1
*/
int Polling(int delay)
{
    char* bmpname[5] = {"./picture/1.bmp", "./picture/2.bmp", "./picture/3.bmp", "./picture/4.bmp", "./picture/5.bmp"};
    int bmpnum = 0;
    int choice;
    show_1152000bmp(bmpname[0], p_lcd); // 显示第一张图片

    do {
        int nTouch = project_touch(&posx, &posy); // 获取触控坐标
        // 判断触控或滑动操作
        if ((nTouch == 0 && posx > 400) || nTouch == 2)      // 点击右侧或左划
            choice = 1;
        else if ((nTouch == 0 && posx < 400) || nTouch == 1) // 点击左侧或右划
            choice = 2;
        else if (nTouch == 4)                                // 上划
            choice = 0;
        
        // 根据选择进行操作
        switch (choice) {
            case 0:
                printf("Exit!\n"); // 退出幻灯片
                break;
            case 1:
                if (bmpnum == 4) {
                    printf("This is the last picture!\n"); // 已经是最后一张
                } else {
                    bmpnum++;
                    show_1152000bmp(bmpname[bmpnum], p_lcd); // 显示下一张图片
                }
                break;
            case 2:
                if (bmpnum == 0) {
                    printf("This is the first picture!\n"); // 已经是第一张
                } else {
                    bmpnum--;
                    show_1152000bmp(bmpname[bmpnum], p_lcd); // 显示上一张图片
                }
                break;
            default:
                printf("Error!\n"); // 出现错误
                break;
        }
    } while (choice != 0);

    return 0;
}
