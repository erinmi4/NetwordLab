#ifndef __LCD_H__
#define __LCD_H__


//LCD初始化
void lcd_init();

//画点函数
void lcd_draw_point(int x,int y,int color);

//关闭LCD
void lcd_close();

//画圆函数
void lcd_draw_circle(int x,int y,int r);

//lcd清屏函数
void lcd_clear();

void lcd_draw_word(int x,int y,int w,int h,unsigned char data[],int color);


#endif