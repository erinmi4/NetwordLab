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

int buttom_x = 0;
int buttom_y = 0;

//显示按键 封装成一个函数
void lcd_show_button()
{
    //画按键 
}

//获取按键的坐标 封装成一个函数
void get_button_index()
{
    //当手指离开开发板保存坐标 
    struct input_event ev;
    // 记录手指触摸和离开屏幕的坐标
    int first_x, first_y;
    int release_x, release_y;
    // 标志位，用于初始化触摸点
    int initialized = 0; 

    while (1) {
        // 检查 read 函数的返回值，确保读取成功
        if (read(touch_fd, &ev, sizeof(ev)) < 0) {
            perror("Error reading touch event");
            return 0; // 读取失败，返回未按下状态
        }
        
        // 处理触摸屏幕的 X 坐标
        if (ev.type == EV_ABS && ev.code == ABS_X) {
            release_x = ev.value;
            if (!initialized) {
                first_x = ev.value;
                initialized = 1;
            }
        }
        
        // 处理触摸屏幕的 Y 坐标
        if (ev.type == EV_ABS && ev.code == ABS_Y) {
            release_y = ev.value;
            if (!initialized) {
                first_y = ev.value;
            }
        }
        
        // 检测手指是否脱离屏幕
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) {
            initialized = 0; // 重置标志位
            
            // 转换坐标到屏幕上的位置，因为触摸坐标和屏幕坐标是不一致的
            release_x = locate_to_lcd_x(release_x);
            release_y = locate_to_lcd_y(release_y);
            
            printf("Touch release at (%d, %d)\n", release_x, release_y);
                //当手指离开开发板 
            button_x = release_x;
            button_y = release_y;
        }
    }
}