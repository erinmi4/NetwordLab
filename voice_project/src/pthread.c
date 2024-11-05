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

// 按键检测线程函数
void *fun(void *arg)
{
    while (1) {
        if (get_rectangle_button_state(touch_fd, 0, 0, X_LENGTH, Y_LENGTH)) {
            lcd_clear(BLUE_COLOR);
            printf("touch success");
        }
        usleep(100000);  // 每 100 ms 检查一次按键状态
    }
    return NULL;  // 确保线程函数有返回值
}

//int main()
//{
//    // 初始化LCD
//    int fd = init_lcd();
//    lcd_clear(BLACK_COLOR);
//    Init_touch();
//
//    char *pic[] = {"./1.bmp", "./2.bmp", "./3.bmp", "./4.bmp", "./ys.bmp"};
//    int total = sizeof(pic) / sizeof(pic[0]);  // 自动计算图片数量
//    int cur_photo = 0; // 当前显示图片索引
//    int max_photo = total - 1 - 2;
//
//    // 创建线程
//    pthread_t tid;
//    int res = pthread_create(&tid, NULL, fun, NULL);
//    if (res != 0) {
//        printf("pthread fail\n");
//        exit(res);
//    }
//    printf("pthread success\n");
//
//    // 循环显示图片
//    while (1) {
//        lcd_show_bmp(0, 0, pic[cur_photo]);
//        cur_photo = (cur_photo == max_photo) ? 0 : cur_photo + 1;  // 切换图片
//        sleep(1);
//    }
//
//    // 等待线程结束
//    pthread_join(tid, NULL);
//    close(fd);
//    return EXIT_SUCCESS;
//}
