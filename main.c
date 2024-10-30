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
    if (fd < 0) {
        perror("Failed to initialize LCD");
        return EXIT_FAILURE;
    }

    // 显示BMP图片
    lcd_show_bmp(100, 100, "./1.bmp");  // 在(0, 0)位置显示图片

    // 关闭LCD
    close_lcd(fd);
    
    return EXIT_SUCCESS;
}
