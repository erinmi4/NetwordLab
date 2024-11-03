#include <pthread.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "draw.h"
#include <stdlib.h>
#include <linux/input.h>
#include "touch.h"
#include "bmp.h"
#include <unistd.h>

int touch_fd;

//创建一个线程函数
void *fun(void *arg)
{
    if(get_rectangle_button_state(touch_fd, 0, 0, X_LENGTH, Y_LENGTH)){
        lcd_clear(BLUE_COLOR);
    }

}



int main()
{
    // 初始化LCD
    int fd = init_lcd();

    lcd_clear(BLACK_COLOR);

    Init_touch();

    char *pic[] = {"./1.bmp", "./2.bmp", "./3.bmp", "./4.bmp", "./ys.bmp"};

    int total = 3;//图片数量
    int cur_photo = 0;//当前打开的图片
    int max_photo = total - 1;


    //按键在图片中的位置
    int icon_x = 300;
    int icon_y = 100;
    int icon_weigh = 200;
    int icon_heigh = 100;

    int begin = total;//默认海报是相册后的第一张
    int icon = total + 1; //按键默认相册后第二张

    //创建一个线程的ID号
    pthread_t tid;
    void *thread_return;
    int res = pthread_create(&tid,NULL,fun,NULL);

    if(res != 0){
        printf("false \n");
        exit(res);
    }

    printf("res create success\n");



    while (1) {
        if (cur_photo == max_photo) {
            cur_photo = 0;
        } else {
            cur_photo++;
        }
        lcd_show_bmp(0, 0, pic[cur_photo]);
        sleep(1);
        
    }


    return EXIT_SUCCESS;

}

