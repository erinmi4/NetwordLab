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


int main() {
    // 初始化LCD
    int fd = init_lcd();

    lcd_clear(BLACK_COLOR);

    int weigh = 16,heigh = 31;
    int cur_x = 100;
    int cur_y = 100;
    int time = 10; //设定倒计时时间为10s
    while(time != 0)
    {
        lcd_show_num(cur_x,cur_y,weigh,heigh,time,RED_COLOR);
        time--;
        sleep(1);
        lcd_clear(BLACK_COLOR);
    }

    close_lcd(fd);

    return EXIT_SUCCESS;
}
