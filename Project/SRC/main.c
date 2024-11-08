//
// Created by 25115 on 2024/11/7.
//

/*
注意文件路径
1.BMP文件路径：/IOT/lab/BMP/
 2.MP3文件路径：/IOT/lab/MP3/
 3.AVI文件路径：/IOT/lab/AVI/
 4.MP4文件路径：/IOT/lab/MP4/
 5.系统图片文件路径：/IOT/lab/Picture/
 6.管道文件路径：/tmp/
 7.启动动画文件路径：/IOT/lab/Start/            需要添加35张图片作为动画显示
*/
#include "../INC/main.h"

/*---------------------------定义全局变量---------------------------*/
int count_BMP = 0;//定义一个用于记录现在图片播到哪的数字(album)
int Control_Num = CONT_INIT;//定义一个用于分辨接收到的控制命令的数字，如果有额外功能，可以作为控制信息。后面可以通过网络编程，使用电脑来操控

int main() {
    /*-------------------------读取文件路径---------------------*/
    struct Filedir * SystemPhotoDir = calloc(1,sizeof(struct Filedir));//系统界面
    struct Filedir * BMPPhotoDir = calloc(1,sizeof(struct Filedir));//定义相册目录结构体指针并为其配置内存空间
    struct Filedir * MP3Dir = calloc(1,sizeof(struct Filedir));  //定义MP3目录结构体指针并为其配置内存空间
    struct Filedir * AVIDir = calloc(1,sizeof(struct Filedir));  //定义AVI目录结构体指针并为其配置内存空间
    Read_SystemDir(SystemPhotoDir,SYSTEM_PHOTO_DIR);//读取系统目录下的文件并进行一定的排序,(系统界面下有独立函数处理)
    Read_Dir(BMPPhotoDir,BMP_PHOTO_DIR,TYPE_BMP);//读取图片路径下的BMP文件
    Read_Dir(MP3Dir,MP3_DIR,TYPE_MP3);//读取图片路径下的内容
    Read_Dir(AVIDir,AVI_DIR,TYPE_AVI);//读取图片路径下的内容
    printf("Read_Dir Finish!\n");
    /*------------------------LCD初始化---------------------*/
    struct Lcd_Init *LCD = calloc(1,sizeof(struct Lcd_Init));//定义LCD结构体指针并为其配置内存空间
    LCD_Init(LCD);//获取打开LCD文件的文件描述符，并为LCD显示的像素点配置内存映射
    printf("LCD Init Finish!");

    /*------------------------触摸初始化---------------------*/
    struct Touch_val *Touch = calloc(1,sizeof(struct Touch_val));//定义触摸屏结构体指针并为其配置内存空间touch
    Touch_Init(Touch);//获取打开触摸屏文件的文件描述符
    printf("Touch Init Finish!\n");

    /*------------------------定义线程相关---------------------*/
    pthread_t Touch_pid;//定义一个用于扫描触摸屏的线程
    pthread_t AVI_pid;//定义一个用于AVI播放的线程
    pthread_t MP3_pid;//定义一个用于MP3播放的线程
    pthread_create(&Touch_pid,NULL,Touch_SCAN,(void *)Touch);//配置扫描触摸屏线程
    printf("Touch_SCAN pthread Init Finish!\n");
    
    Fifo_Init(FIFOPATH_AVI);//查看是否存在AVI的管道文件不存在则建立存在则不操作
    Fifo_Init(FIFOPATH_MP3);//查看是否存在MP3的管道文件不存在则建立存在则不操作

    //开机配置
    Start_System(LCD);//启动开机动画
    LCD_bmp_X_Y(LCD,SystemPhotoDir->FilePath[BACKGROUND_NUM],400,240);//显示主界面图（从中间，向外扩散）

    //记得每次重启后都要打开 bin 文件下面，然后chmod +x mplayer 获取权限，不然不能播放视频
    while (1)
    {
        //MP3播放
        if ((Touch->x > 0 && Touch->x < 260 && Touch->y > 0 && Touch->y < 480 && Touch->Touch_leave == 1)
            ||(Control_Num == MUSIC_PLAY))
        {
            //调用启动MP3播放功能
            MP3_PlayStart(LCD,Touch,MP3Dir,SystemPhotoDir,MP3_pid,&Control_Num);
            //显示主界面图
            LCD_BMPDisplay(LCD,SystemPhotoDir->FilePath[BACKGROUND_NUM],DISPLAY_DOWN,FAST);
        }

        else if ((Touch->x > 260 && Touch->x < 520 && Touch->y > 0 && Touch->y < 480 && Touch->Touch_leave == 1)
                ||(Control_Num == ENTER_KUGOU))
        { 
        //AVI播放
            AVI_PlayStart(LCD,Touch,AVIDir,SystemPhotoDir,AVI_pid,&Control_Num); //调用启动AVI播放器
            LCD_BMPDisplay(LCD,SystemPhotoDir->FilePath[BACKGROUND_NUM],DISPLAY_DOWN,FAST);//显示主界面图
        }
        else if ((Touch->x > 520 && Touch->x < 800 && Touch->y > 0 && Touch->y < 480 && Touch->Touch_leave == 1)
                ||(Control_Num == BACK))
        { 
            //调用启动相册功能
            Album_Start(Touch,LCD,BMPPhotoDir,SystemPhotoDir,&count_BMP,&Control_Num); 
        }
    }
    return 0;
}