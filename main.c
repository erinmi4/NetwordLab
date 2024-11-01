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

    int touch_fd = Init_touch();
    album_show(touch_fd);

    return EXIT_SUCCESS;
}
