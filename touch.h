//
// Created by 25115 on 2024/10/29.
//

#ifndef NETWORKLAB_TOUCH_H
#define NETWORKLAB_TOUCH_H

// 判断方向
#define RIGHT   1
#define LEFT    2
#define UPWARD  3
#define DOWNWARD 4

int draw_fd; // 作为 draw 的文件描述符


int detect_direction(int first_x, int first_y, int end_x, int end_y);
int Init_touch();
void touch_close(int touch_fd);
void Get_abs(int touch_fd);
void Get_touch_direction(int touch_fd);
void dir_switch_color(int dir, int fd);
void touch_to_change_color(int touch_fd, int fd);
#endif // NETWORKLAB_TOUCH_H
