//
// Created by 25115 on 2024/10/29.
//

#ifndef __DRAW_H__
#define __DRAW_H__

#define X_LENGTH 800
#define Y_LENGTH 480
#define RED_COLOR 0xff0000
#define GREEN_COLOR 0x00ff00
#define BLUE_COLOR  0x0000ff


int valid(int x, int y);
int coordinate(int x, int y);
void draw_point(int x, int y, int color,int fd);
int min(int a, int b);
int max(int a, int b);
int in_circle(int x0 , int y0, int x1 , int y1,int radius);

void draw_circle(int x1 , int y1,int radius,int color,int fd);
int init_lcd();
void close_lcd(int fd);
void lcd_clear(int fd);

#endif //__DRAW_H__
