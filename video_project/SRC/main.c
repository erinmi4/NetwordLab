#include "main.h"

/*---------------------------定义全局变量---------------------------*/
int count_BMP = 0;//定义一个用于记录现在图片播到哪的数字
int Control_Num = CONT_INIT;//定义一个用于分辨从手机接收到的控制命令的数字
/*---------------------------定义全局变量---------------------------*/

int main(int argc, char const *argv[])
{
    /*------------打开路径并读取路径下的相关类型文件---------*/
    struct Filedir * SystemPhotoDir = calloc(1,sizeof(struct Filedir));//定义界面图片目录结构体指针并为其配置内存空间
    struct Filedir * BMPPhotoDir = calloc(1,sizeof(struct Filedir));//定义相册目录结构体指针并为其配置内存空间
    struct Filedir * MP3Dir = calloc(1,sizeof(struct Filedir));  //定义MP3目录结构体指针并为其配置内存空间
    struct Filedir * AVIDir = calloc(1,sizeof(struct Filedir));  //定义AVI目录结构体指针并为其配置内存空间
    Read_Dir(BMPPhotoDir,BMP_PHOTO_DIR,TYPE_BMP);//读取图片路径下的BMP文件
    Read_Dir(MP3Dir,MP3_DIR,TYPE_MP3);//读取图片路径下的内容
    Read_Dir(AVIDir,AVI_DIR,TYPE_AVI);//读取图片路径下的内容
    /*------------打开路径并读取路径下的相关类型文件---------*/

    /*------------------------初始化打开特定的文件---------------------*/
    struct Touch_val *Touch = calloc(1,sizeof(struct Touch_val));//定义触摸屏结构体指针并为其配置内存空间
    struct Lcd_Init *LCD = calloc(1,sizeof(struct Lcd_Init));//定义LCD结构体指针并为其配置内存空间
    Touch_Init(Touch);//获取打开触摸屏文件的文件描述符
    LCD_Init(LCD);//获取打开LCD文件的文件描述符，并为LCD显示的像素点配置内存映射


    Fifo_Init(FIFOPATH_AVI);//查看是否存在AVI的管道文件不存在则建立存在则不操作
    Fifo_Init(FIFOPATH_MP3);//查看是否存在MP3的管道文件不存在则建立存在则不操作
    /*------------------------初始化打开特定的文件---------------------*/

    /*------------------------定义线程相关---------------------*/
    pthread_t Touch_pid;//定义一个用于扫描触摸屏的线程
    pthread_t AVI_pid;//定义一个用于AVI播放的线程
    pthread_t MP3_pid;//定义一个用于MP3播放的线程
    pthread_create(&Touch_pid,NULL,Touch_SCAN,(void *)Touch);//配置扫描触摸屏线程
    /*------------------------定义线程相关---------------------*/

    /*------------------------主函数应用---------------------*/
    Start_System(LCD);//启动开机动画
    LCD_bmp_X_Y(LCD,SystemPhotoDir->FilePath[BACKGROUND_NUM],400,240);//显示主界面图
    while (1)//进入程序大循环
    {
        //MP3播放
        else if ((Touch->x > 235 && Touch->x < 365 && Touch->y > 360 && Touch->y < 470 && Touch->Touch_leave == 1)
            ||(Control_Num == MUSIC_PLAY))
        {
            //调用启动MP3播放功能
            MP3_PlayStart(LCD,Touch,MP3Dir,SystemPhotoDir,MP3_pid,&Control_Num);
            //显示主界面图
            LCD_BMPDisplay(LCD,SystemPhotoDir->FilePath[BACKGROUND_NUM],DISPLAY_DOWN,FAST);
        }

        else if ((Touch->x > 455 && Touch->x < 570 && Touch->y > 360 && Touch->y < 470 && Touch->Touch_leave == 1)
                ||(Control_Num == ENTER_KUGOU))
        { 
        //AVI播放
            AVI_PlayStart(LCD,Touch,AVIDir,SystemPhotoDir,AVI_pid,&Control_Num); //调用启动AVI播放器
            LCD_BMPDisplay(LCD,SystemPhotoDir->FilePath[BACKGROUND_NUM],DISPLAY_DOWN,FAST);//显示主界面图
        }
        else if ((Touch->x > 650 && Touch->x < 770 && Touch->y > 360 && Touch->y < 470 && Touch->Touch_leave == 1)
                ||(Control_Num == BACK))
        { 
            //调用启动相册功能
            Album_Start(Touch,LCD,BMPPhotoDir,SystemPhotoDir,&count_BMP,&Control_Num); 
        }
    }
    return 0;
}
