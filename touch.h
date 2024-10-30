//
// Created by 25115 on 2024/10/29.
//

#ifndef NETWORKLAB_TOUCH_H
#define NETWORKLAB_TOUCH_H


int draw_fd;//作为draw的fd

void touch_close(int touch_fd);
int Init_touch();
void Get_abs(int touch_fd);
void Get_touch_direction(int touch_fd);
int detect_direction(int first_x, int first_y, int end_x, int end_y);
void touch_to_switch_color(int dir,int fd);
void touch_to_change_color(int touch_fd,int fd);
#endif //NETWORKLAB_TOUCH_H
