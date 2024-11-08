//
// Created by 25115 on 2024/11/8.
//

#include "../INC/video_music.h"


void * thr_exit;//定义一个空指针用于退出线程
int count_MP3 = 0;//定义一个用于记录现在MP3播到哪的数字
int count_AVI = 0;//定义一个用于记录现在AVI播到哪的数字
int AVI_pid_Num = 1;//定义一个控制AVI线程的数字,初始化为1让它自动播放下一首
int MP3_pid_Num = 1;//定义一个控制MP3线程的数字，初始化为1让它自动播放下一首
/*
    函数名  ：Fifo_Init
    作  用  ：查看管道文件是否存在，如果不存在则创建管道文件
    输入参数：fifopath为管道的创建路径
    返 回 值：无
*/
void Fifo_Init(char * FifoPath)
{
    // 检查管道文件是否存在
    if (access(FifoPath,F_OK))
    {
         // 若不存在则创建管道文件创建管道文件   mkfifo( );
        if(mkfifo(FifoPath,0666)){
            perror("mkfifo  error ");
            exit(1);
        }
        printf("mkfifo success\n");
    }
}
/*
    函数名  ：WR_Fifo
    作  用  ：在指定的管道文件中写入命令
    输入参数：FifoPath - 管道文件的路径，command - 写入的内容
    返 回 值：无
*/
void WR_Fifo(char *FifoPath, char *command) {
    // 打开管道文件
    int fd_fifo = open(FifoPath, O_RDWR); // 使用 O_RDWR 避免因管道没有读者/写者导致的阻塞
    if (fd_fifo == -1) {
        perror("open fifo error");
        return; // 处理错误后直接返回
    }

    // 写入数据
    int ret_val = write(fd_fifo, command, strlen(command));
    if (ret_val <= 0) {
        perror("write fifo error");
    }

    // 关闭管道文件
    close(fd_fifo);
}

/*
    函数名  ：AVI_PlayStart
    作  用  ：进入AVI播放功能
    输入参数：LCD       - LCD结构体指针
             Touch     - 触摸屏结构体指针
             AVIFile   - AVI文件目录结构体指针（播放目录）
             SystemFile - 系统文件目录结构体指针(用来作为背景图)
             AVI_pid   - 主线程中的AVI播放线程。
             Control_Num - 控制标志位指针
    返 回 值：无
    操作说明：上划提升音量10，下滑降低音量10

    管道文件的写入和命令的执行
*/
void AVI_PlayStart(struct Lcd_Init *LCD, struct Touch_val *Touch, struct Filedir *AVIFile, struct Filedir *SystemFile,
                   pthread_t AVI_pid, int *Control_Num) {
    LCD_bmp_X_Y(LCD, SystemFile->FilePath[AVI_STOP_NUM], Touch->x, Touch->y); // 显示AVI播放界面
    Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT; // 初始化触摸标志
    (*Control_Num) = CONT_INIT; // 初始化控制标志
    pthread_create(&AVI_pid, NULL, AVI_PLAY, (void *)AVIFile); // 启动AVI播放线程
    sleep(1); // 短暂延时
    WR_Fifo(FIFOPATH_AVI, "pause\n"); // 初始化暂停状态
    int flag_AVI = 0; // AVI播放状态标志

    printf("AVI Play Start\n");
    while (1) {
        usleep(2000); // 延时
        if ((Touch->x > 335 && Touch->x < 450 && Touch->y > 370 && Touch->Touch_leave == 1)
            || (*Control_Num == MUSIC_STOP_CONT)) { // 暂停/播放切换
            flag_AVI = !flag_AVI; // 切换播放状态
            LCD_BMPDisplay(LCD, SystemFile->FilePath[flag_AVI ? AVI_PLAY_NUM : AVI_STOP_NUM], DISPLAY_NODIR, NO_SPEED);
            (*Control_Num) = CONT_INIT;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            printf("pause the video\n");
            WR_Fifo(FIFOPATH_AVI, "pause\n");
        }
        else if ((Touch->x > 530 && Touch->x < 620 && Touch->y > 380 && Touch->Touch_leave == 1)
                 || (*Control_Num == MUSIC_NEXT)) { // 下一曲
            flag_AVI = 1;
            (*Control_Num) = CONT_INIT;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[AVI_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            AVI_pid_Num = 1;//作为标志位，在线程中，切换状态
            printf("Next AVI Play\n");
            WR_Fifo(FIFOPATH_AVI, "quit\n");
        }
        else if ((Touch->x > 180 && Touch->x < 280 && Touch->y > 380 && Touch->Touch_leave == 1)
                 || (*Control_Num == MUSIC_PREV)) { // 上一曲
            flag_AVI = 1;
            (*Control_Num) = CONT_INIT;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[AVI_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            AVI_pid_Num = 2;
            printf("Previous AVI Play\n");
            WR_Fifo(FIFOPATH_AVI, "quit\n");
        }
        else if (Touch->move_dir == TOUCH_LEFT && Touch->Touch_leave == 1) { // 快退10秒
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[AVI_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("seek -10\n");
            WR_Fifo(FIFOPATH_AVI, "seek -10\n");
        }
        else if (Touch->move_dir == TOUCH_RIGHT && Touch->Touch_leave == 1) { // 快进10秒
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[AVI_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("seek 10\n");
            WR_Fifo(FIFOPATH_AVI, "seek 10\n");
        }
        else if ((Touch->x > 600 && Touch->x < 800 && Touch->y < 400 && Touch->move_dir == TOUCH_UP && Touch->Touch_leave == 1)
                 || (Touch->x > 0 && Touch->x < 200 && Touch->y < 400 && Touch->move_dir == TOUCH_UP && Touch->Touch_leave == 1)
                 || (Touch->x > 685 && Touch->x < 800 && Touch->y > 390 && Touch->Touch_leave == 1)) { // 音量+10
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[AVI_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("volume 10\n");
            WR_Fifo(FIFOPATH_AVI, "volume 10\n");
        }
        else if ((Touch->x > 600 && Touch->x < 800 && Touch->y < 400 && Touch->move_dir == TOUCH_DOWN && Touch->Touch_leave == 1)
                 || (Touch->x > 0 && Touch->x < 200 && Touch->y < 400 && Touch->move_dir == TOUCH_DOWN && Touch->Touch_leave == 1)
                 || (Touch->x > 35 && Touch->x < 120 && Touch->y > 390 && Touch->Touch_leave == 1)) { // 音量-10
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[AVI_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("volume -10\n");
            WR_Fifo(FIFOPATH_AVI, "volume -10\n");
        }
        else if ((Touch->x > 200 && Touch->x < 600 && Touch->move_dir == TOUCH_UP && Touch->Touch_leave == 1)
                 || (*Control_Num == BACK)) { // 退出并返回主菜单
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            (*Control_Num) = CONT_INIT;
            AVI_pid_Num = 5;
            printf("Quit AVI\n");
            WR_Fifo(FIFOPATH_AVI, "quit\n");
            break;
        }
        else if (Touch->move_dir != TOUCH_INIT && Touch->Touch_leave == 1) { // 误操作处理
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
        }
    }
}
/*
    函数名  ：AVI_PLAY
    作  用  ：AVI播放的线程
    输入参数：AVIDir 是AVI目录的结构体指针强制转换而来
    返 回 值：空指针
*/
void* AVI_PLAY(void* AVIDir)
{
    struct Filedir *AVIDIR = (struct Filedir *)AVIDir; // 传参完成类型转换
    char command[130];

    while (1)
    {
        // 播放前置，管道路径，AVI文件路径，初始声音设置
        sprintf(command, "%s%s %s%s", MPLAYER_TIPS2, FIFOPATH_AVI, AVIDIR->FilePath[count_AVI], MPLAYER_INIT_V);
        // 打印命令看是否有问题
        printf("%s\n", command); 

        // 让系统运行播放器
        system(command);

        // 执行完命令后清除命令缓存区的内容
        command[0] = '\0'; // 更好的清空方法
        printf("------------------------Play end------------------------\n"); // 打印播放结束的信息

        // 根据AVI_pid_Num的值决定下一步操作
        if (AVI_pid_Num == 1) // 收到播放下一曲的信息
        {
            count_AVI++; // 播放计数+1，是在播放目录中选择下一个视频
            if (count_AVI > AVIDIR->FileNum - 1)
            {
                count_AVI = 0; // 循环到第一曲
            }
        }
        else if (AVI_pid_Num == 2) // 收到播放上一曲的信息
        {
            AVI_pid_Num = 1; // 恢复线程执行标志位
            count_AVI--; // 播放计数-1
            if (count_AVI < 0)
            {
                count_AVI = AVIDIR->FileNum - 1; // 循环到最后一曲
            }
        }
        else if (AVI_pid_Num == 5) // 收到退出线程的AVI线程的信息
        {
            AVI_pid_Num = 1; // 恢复线程执行标志位
            printf("------------------------Quit AVIPLAYER------------------------\n"); // 打印退出信息
            pthread_exit(thr_exit); // 退出该线程，并将该线程退出信息存储在空指针里
        }
    }

    // 虽然pthread_exit不会被正常执行，但可以明确返回NULL
    return NULL;
}

/*
    函数名  ：MP3_PlayStart
    作  用  ：开启MP3播放功能
    输入参数：
            LCD         LCD结构体指针，用于操作LCD显示
            Touch       触摸屏结构体指针，用于获取触摸屏坐标
            MP3File     MP3目录结构体指针，用于获取MP3文件路径
            SystemFile  系统图片结构体指针，用于获取界面图片路径
            MP3_pid     MP3线程
            Control_Num 用于获取来自网络通信的控制数字
    返 回 值：空指针
*/
void MP3_PlayStart(struct Lcd_Init *LCD, struct Touch_val *Touch, struct Filedir *MP3File,
                   struct Filedir *SystemFile, pthread_t MP3_pid, int *Control_Num)
{
    // 初始化
    (*Control_Num) = CONT_INIT; // 清除标志位
    LCD_bmp_X_Y(LCD, SystemFile->FilePath[MUSIC_STOP_NUM], Touch->x, Touch->y); // 进入MP3播放界面
    Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT; // 清除所有标志位

    // 启动MP3播放线程
    pthread_create(&MP3_pid, NULL, MP3_PLAY, (void *)MP3File);
    sleep(1); // 延时一小会
    WR_Fifo(FIFOPATH_MP3, "pause\n"); // 先暂停

    int flag_MP3 = 0; // 播放标志位

    while (1) {
        usleep(2000); // 延时一小会

        // 暂停/播放控制
        if ((Touch->x > 345 && Touch->x < 460 && Touch->y > 380 && Touch->y < 480 && Touch->Touch_leave == 1) ||
            ((*Control_Num) == MUSIC_STOP_CONT))
        {
            flag_MP3 = !flag_MP3; // 切换播放状态
            LCD_BMPDisplay(LCD, SystemFile->FilePath[flag_MP3 ? MUSIC_PLAY_NUM : MUSIC_STOP_NUM], DISPLAY_NODIR, NO_SPEED); // 切换显示界面
            (*Control_Num) = CONT_INIT; // 清除标志位
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT; // 清除所有标志位
            printf("pause\n");
            WR_Fifo(FIFOPATH_MP3, "pause\n"); // 执行控制命令
        }

        // 下一曲控制
        else if ((Touch->x > 540 && Touch->x < 630 && Touch->y > 390 && Touch->y < 480 && Touch->Touch_leave == 1) ||
                 ((*Control_Num) == MUSIC_NEXT))
        {
            flag_MP3 = 1;
            (*Control_Num) = CONT_INIT;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[MUSIC_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            MP3_pid_Num = 1;
            printf("Next MP3 Play\n");
            WR_Fifo(FIFOPATH_MP3, "quit\n");
        }

        // 上一曲控制
        else if ((Touch->x > 195 && Touch->x < 285 && Touch->y > 390 && Touch->y < 480 && Touch->Touch_leave == 1) ||
                 ((*Control_Num) == MUSIC_PREV))
        {
            flag_MP3 = 1;
            (*Control_Num) = CONT_INIT;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[MUSIC_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            MP3_pid_Num = 2;
            printf("Last MP3 Play\n");
            WR_Fifo(FIFOPATH_MP3, "quit\n");
        }

        // 快进10秒
        else if (Touch->x > 690 && Touch->x < 800 && Touch->y > 390 && Touch->y < 480 && Touch->Touch_leave == 1)
        {
            flag_MP3 = 1;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[MUSIC_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("seek 10\n");
            WR_Fifo(FIFOPATH_MP3, "seek 10\n");
        }

        // 快退10秒
        else if (Touch->x > 40 && Touch->x < 125 && Touch->y > 390 && Touch->y < 480 && Touch->Touch_leave == 1)
        {
            flag_MP3 = 1;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[MUSIC_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("seek -10\n");
            WR_Fifo(FIFOPATH_MP3, "seek -10\n");
        }

        // 音量增减控制
        else if ((Touch->x > 695 && Touch->x < 775 && Touch->y > 60 && Touch->y < 145 && Touch->Touch_leave == 1) ||
                 (Touch->x > 695 && Touch->x < 775 && Touch->y > 230 && Touch->y < 305 && Touch->Touch_leave == 1))
        {
            int volume_change = (Touch->y < 145) ? 10 : -10;
            flag_MP3 = 1;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            LCD_BMPDisplay(LCD, SystemFile->FilePath[MUSIC_PLAY_NUM], DISPLAY_NODIR, NO_SPEED);
            printf("volume %d\n", volume_change);
            WR_Fifo(FIFOPATH_MP3, volume_change > 0 ? "volume 10\n" : "volume -10\n");
        }

        // 返回主菜单
        else if ((Touch->move_dir == TOUCH_UP && Touch->Touch_leave == 1) || ((*Control_Num) == BACK))
        {
            (*Control_Num) = CONT_INIT;
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
            MP3_pid_Num = 5;
            printf("Quit MP3\n");
            WR_Fifo(FIFOPATH_MP3, "quit\n");
            break;
        }

        // 清除误操作标志位
        else if (Touch->move_dir != TOUCH_INIT && Touch->Touch_leave == 1)
        {
            Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT;
        }
    }
}
/*
    函数名  ：MP3_PLAY
    作  用  ：MP3播放的线程
    输入参数：MP3Dir 是AVI目录的结构体指针强制转换而来
    返 回 值：空指针
*/
void* MP3_PLAY(void* MP3Dir) {
    struct Filedir* MP3DIR = (struct Filedir*)MP3Dir;  // 强制转换类型
    char command[130];

    while (1) {
        // 生成播放命令，包括管道路径、文件路径和初始音量
        sprintf(command, "%s%s %s%s", MPLAYER_TIPS1, FIFOPATH_MP3, MP3DIR->FilePath[count_MP3], MPLAYER_INIT_V);
        printf("%s\n", command);  // 打印命令，便于调试
        system(command);  // 执行播放命令

        // 清空命令缓冲区内容
        command[0] = '\0';
        printf("------------------------Play end------------------------\n");  // 打印播放结束信息

        // 根据 MP3_pid_Num 的值确定播放行为
        if (MP3_pid_Num == 1) {  // 播放下一曲
            count_MP3++;
            if (count_MP3 >= MP3DIR->FileNum) {
                count_MP3 = 0;  // 若到达文件末尾，则循环回到第一个文件
            }
        } else if (MP3_pid_Num == 2) {  // 播放上一曲
            MP3_pid_Num = 1;  // 重置执行标志位
            count_MP3--;
            if (count_MP3 < 0) {
                count_MP3 = MP3DIR->FileNum - 1;  // 若小于0，则跳转到最后一个文件
            }
        } else if (MP3_pid_Num == 5) {  // 退出播放线程
            MP3_pid_Num = 1;  // 重置执行标志位
            printf("------------------------Quit AVIPLAYER------------------------\n");  // 打印退出信息
            pthread_exit(NULL);  // 退出线程
        }
    }
}
