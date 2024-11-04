#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

int *plcd = NULL;

//lcd画点函数
void lcd_draw_point(int x,int y,int color)
{
    //画点的前提是这个点的范围在LCD屏幕之中
    if(x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(plcd + x + 800*y) = color;
    }
}

int lcd_show_bmp(int x0,int y0,char* path){
    //1.打开LCD
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(lcd_fd == -1)
    {
        printf("open bmp fial\n");
        return 0;
    }

    //2.映射 
    plcd = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd_fd,0);

    //打开图片文件
    int bmp_fd = open(path,O_RDWR);

    //获取图片的宽度 高度 色深 
    int width;
    lseek(bmp_fd,0x12,SEEK_SET);
    read(bmp_fd,&width,4);
    int heigth;
    lseek(bmp_fd,0x16,SEEK_SET);
    read(bmp_fd,&heigth,4);
    short depth;
    lseek(bmp_fd,0x1c,SEEK_SET);
    read(bmp_fd,&depth,2);

    //获取像素数组
    int line_valid_bytes;//每一行的有效字节数
    int line_bytes;//每一行的实际字节数 = 有效字节数 + 赖子数 
    int total_bytes;//总字节数
    int laizi;//赖子数 

    line_valid_bytes = abs(width) * depth/8;
    //判断是否需要填充赖子 
    if(line_valid_bytes % 4)
    {
        laizi = 4 - line_valid_bytes%4;
    }
    line_bytes = line_valid_bytes + laizi;
    total_bytes = line_bytes * abs(heigth);

    //一口气读取所有的像素数据 
    unsigned char *piexls = malloc(total_bytes);//用数组也可以
    lseek(bmp_fd,54,SEEK_SET);
    read(bmp_fd,piexls,total_bytes);

    //像素数组的解析 
    unsigned char a,r,g,b;//每次保存每个像素点的颜色分量值的每个字节
    int color;//颜色分量,需要处理数据得到
    int i = 0;//帮助遍历像素数组 
    int x,y;//遍历LCD屏幕

    for(y = 0;y < abs(heigth);y++){
        for(x = 0;x < abs(width);x++){
            b = piexls[i++];
            g = piexls[i++];
            r = piexls[i++];
            //在获取色深之前,需要判断是否有色深这一个字节的变量
            if(depth == 32){
                a = piexls[i++];
            }
            else{
                a = 0;
            }
            //合成颜色,显示到对应的位置上
            color = a<<24|r<<16|g<<8|b;
            lcd_draw_point(width>0? x + x0:abs(width)-1-x - x0,heigth>0? abs(heigth)-1-y - y0:y + y0,color);
        }
        //每次遍历完一行之后,跳过赖子数 
        i = i + laizi;
    }


    free(piexls);
    close(bmp_fd);
    return 0;
}

int main(){
    lcd_show_bmp(100,100,"./1.bmp");
    return  0;
}