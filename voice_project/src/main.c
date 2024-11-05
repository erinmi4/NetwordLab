#include <stdio.h>
#include "voicectl.h"

#include <sys/mman.h>
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




int main(int argc,char*argv[])
{
    // 初始化LCDxc
    fd = init_lcd();
    lcd_clear(BLACK_COLOR);
    touch_fd = Init_touch();
	//语音识别
	voicectl(argv[1],touch_fd);
	

	return 0;
}