#ifndef __DRAW_H__
#define __DRAW_H__

#define X_LENGTH 800
#define Y_LENGTH 480
#define RED_COLOR   0xff0000
#define GREEN_COLOR 0x00ff00
#define BLUE_COLOR  0x0000ff
#define BLACK_COLOR 0x000000

// 函数声明
int valid(int x, int y);
int coordinate(int x, int y);
void draw_point(int x, int y, int color);
int min(int a, int b);
int max(int a, int b);
int in_circle(int x0, int y0, int x1, int y1, int radius);
void draw_circle(int x1, int y1, int radius, int color);
int init_lcd();
void close_lcd(int fd);
void lcd_clear(int color);
void Bmp_show(char* path);
void lcd_show_bmp(int x0, int y0, char* path);
void lcd_draw_word(int x,int y,int w,int h,unsigned char data[],int color);
void lcd_draw_number(int x,int y,unsigned char data[],int color);
unsigned char* Get_array_num(int i);
void lcd_draw_numarray(int x, int y, int weigh, int heigh, int data[], int color,int arraysize);
void lcd_show_num(int x,int y,int w,int h,int s,int color);
int locate_to_lcd_y(int y);
int locate_to_lcd_x(int x);

#endif // __DRAW_H__
