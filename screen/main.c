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

int main()
{
    int touch_fd = Init_touch();
    int lcd_fd = init_lcd();
    lcd_clear(BLACK_COLOR);
    //把音乐的背景图片画出来
    Bmp_show("/IOT/lab/music_background.bmp");//音乐背景图
    printf("音频播放背景图片");
    //开始播放音乐
    music_loop("/IOT/lab/music/This World.mp3");
    printf("音乐开始播放");
    //music_draw();
    printf("等待动作");
    //等待动作
    while(1)
    {
        //暂停
        if(get_rectangle_button_state(touch_fd, 400, 200, 100, 50))
        {
            printf("暂停\n");
            music_stop();

        }
        //播放
        if(get_rectangle_button_state(touch_fd, 400, 250, 100, 50))
        {
            printf("播放\n");
            music_continue();
        }
        //下一曲
        if(get_rectangle_button_state(touch_fd, 400, 300, 100, 50))
        {
            printf("下一曲\n");
            music_cancel();
        }

        //上一曲
        if(get_rectangle_button_state(touch_fd, 400, 350, 100, 50))
        {
            printf("上一曲\n");
            music_cancel();
        }
    }
}
