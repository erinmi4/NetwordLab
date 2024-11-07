#ifndef __BUTTOM_H__
#define __BUTTOM_H__

void get_button_index();
void lcd_show_button();
//判断坐标在一个圆内
int is_in_circle(int x, int y, int center_x, int center_y, int radius);
//判断坐标在一个矩形内,给出该矩形的左上角的坐标和长宽
int is_in_rectangle(int x, int y, int rect_x, int rect_y, int rect_width, int rect_height);
#endif