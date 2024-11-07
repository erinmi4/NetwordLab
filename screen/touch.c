//
// Created by 25115 on 2024/10/29.
//

#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "touch.h"
#include "draw.h"
#include <linux/input.h>

// 坐标范围 600 * 1024

// 根据开始坐标和结束坐标，判断方向 1 右 2 左 3 上 4 下
int detect_direction(int first_x, int first_y, int end_x, int end_y) {
    if (abs(end_x - first_x) > abs(end_y - first_y)) {
        // x轴位移更大，判断左右滑动
        if (end_x > first_x) {
            printf("Right\n");
            return RIGHT;
        } else {
            printf("Left\n");
            return LEFT;
        }
    } else {
        // y轴位移更大，判断上下滑动
        if (end_y > first_y) {
            printf("Upward\n");
            return UPWARD;
        } else {
            printf("Downward\n");
            return DOWNWARD;
        }
    }
}

/* 初始化触摸事件的文件描述符 */
int Init_touch() {
    int touch_fd = open("/dev/input/event0", O_RDWR);
    if (touch_fd == -1) {
        perror("Open touch event file error");
        exit(EXIT_FAILURE);
    }
    return touch_fd;
}

/* 关闭触摸事件的文件描述符 */
void touch_close(int touch_fd) {
    close(touch_fd);
}

/* 获取触摸位置 */
void Get_abs(int touch_fd) {
    struct input_event ev;
    int x = -1, y = -1;

    while (1) {
        read(touch_fd, &ev, sizeof(ev));
        if (ev.type == EV_ABS && ev.code == ABS_X) {
            x = ev.value;
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y) {
            y = ev.value;
        }
        printf("(%d,%d)\n", x, y);
    }
}

/* 一直获取滑动的方向 */
void Get_touch_direction(int touch_fd) {
    struct input_event ev;
    int first_x, first_y;
    int recode_x, recode_y;
    int dir = 0;
    int initialized = 0; // 标志位

    while (1) {
        read(touch_fd, &ev, sizeof(ev));
        if (ev.type == EV_ABS && ev.code == ABS_X) {
            recode_x = ev.value;
            if (!initialized) {
                first_x = ev.value;
                initialized = 1;
            }
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y) {
            recode_y = ev.value;
            if (!initialized) {
                first_y = ev.value;
            }
        }
        // 判断手是否脱离屏幕
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) {
            printf("%d %d %d %d\n", first_x, first_y, recode_x, recode_y);
            dir = detect_direction(first_x, first_y, recode_x, recode_y);
            initialized = 0; // 重置标志位
        }
    }
}

/* 根据不同的方向进行颜色变换 */
void dir_switch_color(int dir) {
    switch (dir) {
        case RIGHT:
            lcd_clear(RED_COLOR);
            break;
        case LEFT:
            lcd_clear(GREEN_COLOR);
            break;
        case UPWARD:
            lcd_clear(BLUE_COLOR);
            break;
        case DOWNWARD:
            lcd_clear(BLACK_COLOR);
            break;
        default:
            break;
    }
}

/* 通过记录滑动方向进行颜色变化 */
void touch_to_change_color(int touch_fd) {
    struct input_event ev;
    int first_x, first_y;
    int recode_x, recode_y;
    int dir = 0;
    int initialized = 0; // 标志位

    while (1) {
        read(touch_fd, &ev, sizeof(ev));

        if (ev.type == EV_ABS && ev.code == ABS_X) {
            recode_x = ev.value;
            if (!initialized) {
                first_x = ev.value;
                initialized = 1;
            }
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y) {
            recode_y = ev.value;
            if (!initialized) {
                first_y = ev.value;
            }
        }
        // 判断手是否脱离屏幕
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) {
            printf("%d %d %d %d\n", first_x, first_y, recode_x, recode_y);
            dir = detect_direction(first_x, first_y, recode_x, recode_y);
            dir_switch_color(dir);
            initialized = 0; // 重置标志位
        }
    }
}

/* 
 * 获取按键的状态，返回1说明按下，返回0说明没有按下
 * 参数 touch_fd 是触摸设备文件描述符
 * locate_x, locate_y 是按键图片左上角的坐标
 * width 和 height 是按键的宽度和高度
 */
int get_rectangle_button_state(int touch_fd, int locate_x, int locate_y, int width, int height) {
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
            
            // 判断释放点是否在按钮区域内部
            return in_rectangle(locate_x, locate_y, release_x, release_y, width, height);
        }
    }
}



/* 一直获取滑动的方向 */
int Get_touch_dir(int touch_fd) {
    struct input_event ev;
    int first_x, first_y;
    int recode_x, recode_y;
    int dir = 0;
    int initialized = 0; // 标志位

    while (1) {
        read(touch_fd, &ev, sizeof(ev));
        if (ev.type == EV_ABS) {
            if (ev.code == ABS_X) {
                recode_x = ev.value;
                if (!initialized) {
                    first_x = ev.value;
                    initialized = 1;
                }
            }
            if (ev.code == ABS_Y) {
                recode_y = ev.value;
                if (!initialized) {
                    first_y = ev.value;
                }
            }
        }
        // 判断手是否脱离屏幕
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) {
            printf("%d %d %d %d\n", first_x, first_y, recode_x, recode_y);
            dir = detect_direction(first_x, first_y, recode_x, recode_y);
            initialized = 0; // 重置标志位
            return dir;
        }
    }
}

