#include <sys/types.h>          /* See NOTES */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <math.h>
#include "draw.h"
//#include "charlib.h"
#include "touch.h"
#include "bmp.h"
#include "music.h"
#include "video.h"
#include "buttom.h"

extern int buttom_x;// 按键坐标
extern int buttom_y;// 按键坐标
extern char *video_list[];//视频列表

// 按键检测线程函数
void *fun(void *arg)
{
    while (1) {
        get_button_index();
    }
}

int main()
{
    // 创建线程
    pthread_t tid;
    int res = pthread_create(&tid, NULL, fun, NULL);
    if (res != 0) {
        printf("pthread fail\n");
        exit(res);
    }
    printf("pthread success\n");

    // 初始化触摸屏和LCD
    int touch_fd = Init_touch();
    int lcd_fd = init_lcd();
    lcd_clear(BLACK_COLOR);
    //把视频的背景图片画出来
    Bmp_show("/IOT/lab/video_background.bmp");//视频背景图
    printf("video background show success\n");

    printf("Waiting for action...\n");
    //等待动作，根据动作，执行不同的任务
    while(1)
    {
        //上一个视频

        //下一个视频

        //播放视频

        //暂停视频

        //继续视频

        //取消视频

        //循环播放视频

        //退出程序


    }
}
