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
        if (ev.type == EV_ABS) {
            if (ev.code == ABS_X) {
                x = ev.value;
            }
            if (ev.code == ABS_Y) {
                y = ev.value;
            }
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
            dir_switch_color(dir);
            initialized = 0; // 重置标志位
        }
    }
}

/*
返回1说明按下，返回0，说明没有按下
 给出按键圆心
*/
int get_button_state(int touch_fd,int locate_x,int locate_y,int radius)//获取按键的状态
{
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
            dir_switch_color(dir);
            initialized = 0; // 重置标志位
            //判断是否处于按键区域内部。
            return in_circle(recode_x,recode_y,locate_y,locate_y,radius) ? 1:0;
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
