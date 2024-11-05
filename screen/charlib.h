//
// Created by 25115 on 2024/10/31.
//

#ifndef NETWORKLAB_CHARLIB_H
#define NETWORKLAB_CHARLIB_H

/*--  文字:  0  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char zero[24 * 46 / 8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFE,
0x00,0x07,0xFF,0x00,0x0F,0xFF,0x80,0x1F,0x9F,0xC0,0x1F,0x07,0xC0,0x3E,0x07,0xE0,
0x3E,0x03,0xE0,0x3C,0x03,0xE0,0x7C,0x03,0xE0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x7C,
0x01,0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x7C,0x01,
0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xE0,0x7C,0x03,0xE0,0x7C,0x03,0xE0,0x3E,0x03,0xE0,
0x3E,0x07,0xC0,0x1F,0x0F,0xC0,0x1F,0xFF,0x80,0x0F,0xFF,0x00,0x07,0xFE,0x00,0x00,
0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


/*--  文字:  1  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char one[24 * 46 / 8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,
0x00,0x00,0x7C,0x00,0x01,0xFC,0x00,0x0F,0xFC,0x00,0x1F,0xFC,0x00,0x1F,0xFC,0x00,
0x1E,0x7C,0x00,0x18,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,
0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,
0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,
0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/*--  文字:  2  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char two[24 * 46 / 8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFC,
0x00,0x0F,0xFF,0x00,0x1F,0xFF,0x80,0x3F,0x1F,0xC0,0x3C,0x07,0xC0,0x38,0x07,0xC0,
0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x03,0xC0,0x00,0x07,0xC0,0x00,
0x0F,0xC0,0x00,0x0F,0x80,0x00,0x3F,0x00,0x00,0x7E,0x00,0x00,0xFC,0x00,0x03,0xF8,
0x00,0x07,0xF0,0x00,0x0F,0xC0,0x00,0x1F,0x80,0x00,0x1F,0x00,0x00,0x3E,0x00,0x00,
0x3C,0x00,0x00,0x7C,0x00,0x00,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/*--  文字:  3  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char three[24 * 46 / 8] ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFC,
0x00,0x1F,0xFE,0x00,0x1F,0xFF,0x00,0x1E,0x1F,0x80,0x18,0x0F,0x80,0x00,0x07,0xC0,
0x00,0x07,0xC0,0x00,0x07,0xC0,0x00,0x07,0xC0,0x00,0x0F,0x80,0x00,0x1F,0x80,0x00,
0xFF,0x00,0x0F,0xFE,0x00,0x0F,0xFE,0x00,0x0F,0xFF,0x00,0x00,0x1F,0x80,0x00,0x0F,
0xC0,0x00,0x07,0xC0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x07,0xC0,
0x00,0x07,0xC0,0x38,0x0F,0xC0,0x3F,0xFF,0x80,0x3F,0xFF,0x00,0x3F,0xFE,0x00,0x07,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

/*--  文字:  4  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char four[24 * 46 / 8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,
0x00,0x00,0x1F,0x80,0x00,0x1F,0x80,0x00,0x3F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x80,
0x00,0xFF,0x80,0x00,0xFF,0x80,0x01,0xFF,0x80,0x03,0xEF,0x80,0x03,0xCF,0x80,0x07,
0xCF,0x80,0x0F,0x8F,0x80,0x1F,0x0F,0x80,0x1F,0x0F,0x80,0x3E,0x0F,0x80,0x7C,0x0F,
0x80,0xF8,0x0F,0x80,0xFF,0xFF,0xF8,0xFF,0xFF,0xF8,0xFF,0xFF,0xF8,0x00,0x0F,0x80,
0x00,0x0F,0x80,0x00,0x0F,0x80,0x00,0x0F,0x80,0x00,0x0F,0x80,0x00,0x0F,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

/*--  文字:  5  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char five[24 * 46 / 8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,
0x80,0x0F,0xFF,0x80,0x1F,0xFF,0x80,0x1F,0xFF,0x80,0x1F,0x00,0x00,0x1F,0x00,0x00,
0x1F,0x00,0x00,0x1F,0x00,0x00,0x1F,0x00,0x00,0x1E,0x00,0x00,0x1E,0xC0,0x00,0x1F,
0xFC,0x00,0x1F,0xFF,0x00,0x1F,0xFF,0x80,0x00,0x1F,0xC0,0x00,0x0F,0xC0,0x00,0x07,
0xC0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x07,0xC0,
0x00,0x07,0xC0,0x38,0x1F,0xC0,0x3F,0xFF,0x80,0x3F,0xFF,0x00,0x3F,0xFE,0x00,0x07,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

/*--  文字:  6  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char six[24 * 46 / 8] ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,
0xC0,0x01,0xFF,0xC0,0x03,0xFF,0xC0,0x07,0xE1,0xC0,0x0F,0xC0,0x00,0x1F,0x80,0x00,
0x1F,0x00,0x00,0x1E,0x00,0x00,0x3E,0x00,0x00,0x3E,0x00,0x00,0x3C,0x7E,0x00,0x3D,
0xFF,0x80,0x7F,0xFF,0xC0,0x7F,0xFF,0xC0,0x7F,0x07,0xE0,0x7E,0x03,0xE0,0x7E,0x01,
0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x3C,0x01,0xF0,0x3E,0x01,0xF0,0x3E,0x03,0xE0,
0x1F,0x03,0xE0,0x1F,0x87,0xE0,0x0F,0xFF,0xC0,0x07,0xFF,0x80,0x03,0xFF,0x00,0x00,
0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

/*--  文字:  7  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char seven[24 * 46 / 8] ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,
0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x7F,0xFF,0xE0,0x00,0x03,0xC0,0x00,0x07,0xC0,
0x00,0x07,0x80,0x00,0x0F,0x80,0x00,0x0F,0x00,0x00,0x1F,0x00,0x00,0x1E,0x00,0x00,
0x3E,0x00,0x00,0x3C,0x00,0x00,0x7C,0x00,0x00,0x7C,0x00,0x00,0xF8,0x00,0x00,0xF8,
0x00,0x00,0xF0,0x00,0x01,0xF0,0x00,0x01,0xF0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,
0x03,0xE0,0x00,0x03,0xE0,0x00,0x07,0xC0,0x00,0x07,0xC0,0x00,0x07,0xC0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

/*--  文字:  8  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char eight[24 * 46 / 8] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFC,
0x00,0x07,0xFF,0x00,0x0F,0xFF,0x80,0x1F,0x8F,0xC0,0x3F,0x07,0xC0,0x3E,0x03,0xC0,
0x3E,0x03,0xC0,0x3E,0x03,0xC0,0x3E,0x03,0xC0,0x1E,0x07,0xC0,0x1F,0x8F,0x80,0x0F,
0xFF,0x00,0x07,0xFE,0x00,0x0F,0xFF,0x80,0x1F,0xFF,0xC0,0x3F,0x07,0xC0,0x3E,0x03,
0xE0,0x7C,0x01,0xE0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xF0,0x7C,0x01,0xE0,
0x7E,0x03,0xE0,0x3F,0x07,0xE0,0x1F,0xFF,0xC0,0x0F,0xFF,0x80,0x07,0xFF,0x00,0x00,
0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
/*--  文字:  9  --*/
/*--  微软雅黑26;  此字体下对应的点阵为：宽x高=21x46   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=24x46  --*/
unsigned char nine[24 * 46 / 8] ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFC,
0x00,0x0F,0xFF,0x00,0x1F,0xFF,0x80,0x1F,0x9F,0x80,0x3E,0x07,0xC0,0x3E,0x07,0xC0,
0x7C,0x03,0xE0,0x7C,0x03,0xE0,0x7C,0x03,0xE0,0x7C,0x03,0xE0,0x7C,0x03,0xE0,0x7C,
0x03,0xE0,0x3E,0x07,0xE0,0x3F,0x0F,0xE0,0x1F,0xFF,0xE0,0x0F,0xFF,0xE0,0x07,0xFF,
0xE0,0x00,0xE3,0xE0,0x00,0x03,0xE0,0x00,0x03,0xE0,0x00,0x07,0xC0,0x00,0x07,0xC0,
0x00,0x0F,0x80,0x30,0x1F,0x80,0x3F,0xFF,0x00,0x3F,0xFE,0x00,0x3F,0xF8,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};



//数字0到9的字模
unsigned char shu[10][16*31/8] = { {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x1F,0xE0,
                                    0x3F,0xF0,0x3C,0x78,0x78,0x78,0x78,0x78,0x70,0x3C,0xF0,0x3C,0xF0,0x3C,0xF0,0x3C,
                                    0xF0,0x3C,0xF0,0x3C,0xF0,0x3C,0x70,0x38,0x78,0x78,0x78,0x78,0x3C,0xF0,0x3F,0xF0,
                                    0x1F,0xE0,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xC0,0x03,0xC0,
                                    0x0F,0xC0,0x3F,0xC0,0x3F,0xC0,0x33,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,
                                    0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,
                                    0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,0x3F,0xE0,
                                    0x7F,0xF0,0x78,0xF8,0x60,0x78,0x00,0x78,0x00,0x78,0x00,0x78,0x00,0xF0,0x01,0xF0,
                                    0x03,0xE0,0x0F,0xC0,0x1F,0x00,0x3E,0x00,0x3C,0x00,0x78,0x00,0x78,0x00,0x7F,0xFC,
                                    0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,0x3F,0xE0,
                                    0x3F,0xF0,0x30,0xF0,0x00,0xF0,0x00,0x70,0x00,0xF0,0x00,0xF0,0x1F,0xE0,0x1F,0xC0,
                                    0x1F,0xF0,0x00,0xF0,0x00,0x78,0x00,0x78,0x00,0x78,0x00,0x78,0x70,0xF0,0x7F,0xF0,
                                    0x7F,0xE0,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x01,0xF0,
                                    0x01,0xF0,0x03,0xF0,0x03,0xF0,0x07,0xF0,0x0F,0xF0,0x0E,0xF0,0x1E,0xF0,0x3C,0xF0,
                                    0x78,0xF0,0x78,0xF0,0xFF,0xFC,0xFF,0xFC,0xFF,0xFC,0x00,0xF0,0x00,0xF0,0x00,0xF0,
                                    0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF0,0x3F,0xF0,
                                    0x3F,0xF0,0x3C,0x00,0x3C,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x3F,0xC0,0x3F,0xF0,
                                    0x01,0xF0,0x00,0x78,0x00,0x78,0x00,0x78,0x00,0x78,0x00,0x78,0x70,0xF0,0x7F,0xF0,
                                    0x7F,0xE0,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF0,0x0F,0xF8,
                                    0x1F,0xF8,0x1E,0x00,0x3C,0x00,0x38,0x00,0x78,0x00,0x7B,0xC0,0x7F,0xF0,0x7F,0xF8,
                                    0x7C,0x78,0x78,0x3C,0x78,0x3C,0x78,0x3C,0x78,0x3C,0x78,0x38,0x3C,0x78,0x3F,0xF0,
                                    0x1F,0xE0,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xF8,0x7F,0xFC,
                                    0x7F,0xF8,0x00,0x78,0x00,0x70,0x00,0xF0,0x00,0xE0,0x01,0xE0,0x01,0xC0,0x03,0xC0,
                                    0x03,0x80,0x07,0x80,0x07,0x80,0x07,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x1E,0x00,
                                    0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x1F,0xE0,
                                    0x3F,0xF0,0x3C,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x3C,0xF0,0x1F,0xE0,0x1F,0xE0,
                                    0x3F,0xF0,0x78,0x78,0x70,0x38,0xF0,0x3C,0xF0,0x3C,0x70,0x38,0x78,0x78,0x3F,0xF0,
                                    0x1F,0xE0,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x1F,0xE0,
                                    0x3F,0xF0,0x78,0xF8,0x78,0x78,0x70,0x78,0xF0,0x38,0xF0,0x3C,0x78,0x7C,0x7C,0xFC,
                                    0x3F,0xFC,0x1F,0xF8,0x07,0x38,0x00,0x78,0x00,0x78,0x00,0xF0,0x21,0xF0,0x7F,0xE0,
                                    0x7F,0xC0,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};


#endif //NETWORKLAB_CHARLIB_H