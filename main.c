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



int main() {
    // 初始化LCD
    int fd = init_lcd();

    lcd_clear(BLACK_COLOR);

    int data[] = {1,1,4,5,1,4};

    lcd_draw_numarray(0,0,24,46,data,RED_COLOR);
    close_lcd(fd);

    return EXIT_SUCCESS;
}
