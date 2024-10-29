//
// Created by 25115 on 2024/10/29.
//

#ifndef NETWORKLAB_TOUCH_H
#define NETWORKLAB_TOUCH_H




void touch_close(int touch_fd);
int Init_touch();
void Get_abs(int touch_fd);
void Get_touch_direction(int touch_fd);
void detect_direction(int first_x, int first_y, int end_x, int end_y);

#endif //NETWORKLAB_TOUCH_H
