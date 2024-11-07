#include "main.h"

// 项目程序初始化
int project_init(void)
{
    // 打开LCD文件
    fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd == -1) {
        perror("Open LCD failed");
        return -1;
    }

    // 内存映射
    /* LCD屏幕映射到p_lcd */
    p_lcd = (int *)mmap(NULL, PIXELS * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
    if (p_lcd == MAP_FAILED) {
        perror("LCD mmap failed");
        close(fd_lcd);
        return -1;
    }

    // 打开触摸屏文件
    fd_touch = open("/dev/input/event0", O_RDONLY);
    if (fd_touch == -1) {
        perror("Open touch screen failed");
        munmap(p_lcd, PIXELS * 4);
        close(fd_lcd);
        return -1;
    }

    // 创建管道文件
    if (access("/fifo", F_OK) != 0) { // F_OK: 判断是否存在
        if (mkfifo("/fifo", 0666) == -1) { // 创建管道文件
            perror("Create fifo failed");
            munmap(p_lcd, PIXELS * 4);
            close(fd_lcd);
            close(fd_touch);
            return -1;
        }
    }

    // 打开管道文件
    fd_fifo = open("/fifo", O_RDWR);
    if (fd_fifo == -1) {
        perror("Open fifo failed");
        munmap(p_lcd, PIXELS * 4);
        close(fd_lcd);
        close(fd_touch);
        return -1;
    }

    return 0;
}

// 程序项目关闭
int project_destroy(void)
{
    int ret;

    // 关闭LCD文件
    ret = close(fd_lcd);
    if (ret == -1) {
        perror("Close LCD failed");
        return -1;
    }

    // 解除内存映射
    munmap(p_lcd, PIXELS * 4);

    // 关闭触摸屏文件
    ret = close(fd_touch);
    if (ret == -1) {
        perror("Close touch screen failed");
        return -1;
    }

    // 关闭管道文件
    ret = close(fd_fifo);
    if (ret == -1) {
        perror("Close fifo failed");
        return -1;
    }

    return 0;
}
