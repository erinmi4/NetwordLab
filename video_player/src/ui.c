#include "main.h"

// 菜单选择
/*
    输入：无
    输出：显示菜单以及选择的菜单项
    返回值：选择的菜单项 0~4
*/
int ChoiceSelect(void)
{
    int choices = 4;

    // 显示菜单背景图片
    show_1152000bmp("./picture/background.bmp", p_lcd);

    // 获取点击坐标
    int SlideMode = project_touch(&posx, &posy);
    printf("posx = %d, posy = %d\nSlideMode = %d\n", posx, posy, SlideMode); // 调试输出

    // 判断选择的菜单项
    if (posx > 0 && posx < 800 / 4 && posy > 240 && posy < 480) 
        return 1;
    else if (posx > 800 / 4 && posx < 800 / 4 * 2 && posy > 240 && posy < 480) 
        return 2;
    else if (posx > 800 / 4 * 2 && posx < 800 / 4 * 3 && posy > 240 && posy < 480) 
        return 3;
    else if (posx > 800 / 4 * 3 && posx < 800 / 4 * 4 && posy > 240 && posy < 480) 
        return 4;
    else 
        return 0;
}

// UI界面
int project_ui(void)
{
    /* 函数声明 */
    int Polling(int);
    int MusicPlay(char[]);
    int VideoPlay(char[], int, int);

    // 1.开机提示
    printf("Welcome to my project!!\n");
    printf("-------------------------\n");
    printf("PICTURE: 1.picture polling\n2.music playing\n3.video playing\n");

    // 显示开机界面
    show_1152000bmp("./picture/Photo_tip.bmp", p_lcd);
    system("mplayer ./music/Thisstreet.mp3 &");
    sleep(4);
    system("killall -9 mplayer");
    sleep(3);

    // 显示菜单背景
    show_1152000bmp("./picture/background.bmp", p_lcd);
    system("killall -9 mplayer"); // 防止音乐复活

    // 2.项目功能选择
    int choice;
    do {
        // 提示选择项目
        choice = ChoiceSelect();
        printf("Menu load success!\n");

        switch (choice) {
            case 0: // 退出
                printf("Exit!\n");
                break;

            case 1: // 幻灯片播放
                Polling(3);
                break;

            case 2: // 音乐播放
                MusicPlay("./music/Thisstreet.mp3");
                break;

            case 3: // 视频播放
                VideoPlay("./video/kungfu.avi", 800, 400);
                break;

            case 4: // 未知功能
                Lcd_Init();
                Dis_pic("./picture/1.bmp"); // 显示封面图片
                Get_ev(&x, &y); // 开始操作
                printf("What are you doing?\n");
                break;

            default: // 输入错误
                printf("You want to destroy me??\n");
                break;
        }
    } while (choice != 0); // 循环直到选择退出

    return 0;
}
