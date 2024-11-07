#include "main.h"

// 音乐播放函数
/*
    输入：音乐文件路径
    输出：音乐播放
    返回：成功返回0，失败返回-1
*/
int MusicPlay(char musicpath[]) {
    int posx, posy;  // 触摸坐标
    int choice;      // 用户选择
    int MusicMode = 1;  // 播放模式：1表示播放，0表示暂停

    // 显示播放界面
    show_1152000bmp("./picture/music_play.bmp", p_lcd);
    // 停止可能存在的 mplayer 进程并打开音乐文件
    system("killall -9 mplayer");
    
    // 启动音乐播放
    char Music[255];
    sprintf(Music, "mplayer %s &", musicpath);
    system(Music);

    // 用户交互循环
    do {
        int nTouch = project_touch(&posx, &posy);

        // 根据触摸坐标判定用户选择
        if (posx > 300 && posx < 490 && posy > 100 && posy < 300) {
            choice = 1;  // 暂停或继续音乐
        } else if (posx > 250 && posx < 540 && posy > 330 && posy < 430) {
            choice = 0;  // 退出音乐
        } else if (posx > 60 && posx < 160 && posy > 330 && posy < 430) {
            choice = 2;  // 音量减小
        } else if (posx > 630 && posx < 730 && posy > 330 && posy < 430) {
            choice = 3;  // 音量增加
        } else if (posx > 0 && posx < 130 && posy > 100 && posy < 300) {
            choice = 4;  // 快退
        } else if (posx > 660 && posx < 800 && posy > 100 && posy < 300) {
            choice = 5;  // 快进
        } else {
            choice = -1;  // 未知操作
        }

        // 根据选择执行相应操作
        switch (choice) {
            case 0:  // 退出音乐
                system("killall -SIGKILL mplayer");
                break;
                
            case 1:  // 暂停或继续音乐
                if (MusicMode == 1) {
                    system("killall -SIGSTOP mplayer");
                    MusicMode = 0;
                    show_1152000bmp("./picture/music_stop.bmp", p_lcd);
                } else {
                    system("killall -SIGCONT mplayer");
                    MusicMode = 1;
                    show_1152000bmp("./picture/music_play.bmp", p_lcd);
                }
                break;
                
            case 2:  // 音量减小
                Send_Cmd("volume -10\n");
                break;
                
            case 3:  // 音量增加
                Send_Cmd("volume +10\n");
                break;
                
            case 4:  // 快退
                Send_Cmd("seek -10\n");
                break;
                
            case 5:  // 快进
                Send_Cmd("seek +10\n");
                break;
                
            default:  // 未知操作
                printf("Error: Unknown touch input!\n");
                break;
        }
        
    } while (choice != 0);

    return 0;
}
