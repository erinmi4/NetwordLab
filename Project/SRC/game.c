#include "game.h"

// 全局控制变量
static int stopFlag;   // 0：暂停，1：开始
static int isExit;     // 0：继续，1：游戏结束
static int isReset;    // 0：不重新开始，1：重新开始

// 分数图片路径
static const char *score_buf[] = {
    "./rec/0.bmp", "./rec/1.bmp", "./rec/2.bmp", "./rec/3.bmp",
    "./rec/4.bmp", "./rec/5.bmp", "./rec/6.bmp", "./rec/7.bmp",
    "./rec/8.bmp", "./rec/9.bmp"
};

// 初始化游戏，创建必要的线程
int GameInit() {
    ShowBmp(0, 0, "./rec/p_c.bmp"); // 显示游戏界面

    if (pthread_create(&PI.pid1, NULL, MoveBall, NULL) != 0) {
        perror("创建小球移动线程失败！");
        return -1;
    }
    if (pthread_create(&PI.pid2, NULL, TouchControlPlate, NULL) != 0) {
        perror("创建触摸控制线程失败！");
        return -1;
    }

    isExit = 0;
    stopFlag = 0;
    isReset = 0;
    return 0;
}

// 游戏资源清理
int GameFree() {
    ShowBmp(0, 0, "./rec/main.bmp");
    return 0;
}

// 显示当前得分
void ShowScore(int score) {
    int i = 0;
    while (score > 0 || i == 0) { // 至少显示一位
        int digit = score % 10;
        ShowBmp(767 - (i * 32), 10, score_buf[digit]);
        score /= 10;
        i++;
    }
}

// 移动小球线程函数
void* MoveBall(void *arg) {
    int score = 0;
    int x0 = 400, y0 = 240;       // 小球初始位置
    int r = 50;                    // 半径
    int x_mask = 0, y_mask = 0;    // 方向标志

    while (1) {
        DrawBall(x0, y0, r); // 绘制小球
        usleep(3000);        // 控制小球移动速度

        // 暂停或重新开始处理
        if (stopFlag == 0 && isReset == 1) {
            ResetBall(&x0, &y0, &x_mask, &y_mask, &score);
        }

        // 更新小球位置
        UpdateBallPosition(&x0, &y0, &x_mask, &y_mask, &score);

        // 判断游戏是否结束
        if (isExit) break;
    }

    return NULL;
}

// 重置小球位置及分数
void ResetBall(int *x0, int *y0, int *x_mask, int *y_mask, int *score) {
    *x0 = 400;
    *y0 = 240;
    *x_mask = 0;
    *y_mask = 0;
    *score = 0;
    stopFlag = 0;
    isReset = 0;
    ShowBmp(0, 0, "./rec/p_c.bmp");
}

// 绘制小球
void DrawBall(int x0, int y0, int r) {
    int x, y;
    for (y = y0 - r; y <= y0 + r; y++) {
        for (x = x0 - r; x <= x0 + r; x++) {
            if ((x - x0) * (x - x0) + (y - y0) * (y - y0) < r * r) {
                PI.mmap_addr[800 * y + x] = 0x0000ff; // 蓝色像素
            } else {
                PI.mmap_addr[800 * y + x] = 0xffffff; // 白色背景
            }
        }
    }
}

// 更新小球位置和方向
void UpdateBallPosition(int *x0, int *y0, int *x_mask, int *y_mask, int *score) {
    if (*y0 - 50 <= 0)   *y_mask = 1; // 上边
    if (*x0 - 50 <= 0)   *x_mask = 1; // 左边
    if (*y0 + 50 == 399 && *x0 > PI.Ts_x - 50 && *x0 < PI.Ts_x + 50) {
        *y_mask = 0;
        (*score)++;
        ShowScore(*score);
    }
    if (*y0 + 50 >= 410) isExit = 1;  // 下边未接住
    if (*x0 + 50 >= 696) *x_mask = 0; // 右边

    *y0 += (*y_mask == 1) ? 1 : -1;
    *x0 += (*x_mask == 1) ? 1 : -1;
}

// 绘制木板
void DrawPlate() {
    int x, y;
    for (y = 400; y < 430; y++) {
        for (x = 0; x < 696; x++) {
            PI.mmap_addr[800 * y + x] = (x > PI.Ts_x - 50 && x < PI.Ts_x + 50) ? 0x0000ff : 0xffffff;
        }
    }
}

// 触摸控制线程函数
void* TouchControlPlate(void *arg) {
    while (1) {
        Get_Xy(); // 获取触摸坐标
        if (PI.Ts_y > 400 && PI.Ts_y < 430) DrawPlate(); // 控制木板

        if (CheckTouch(700, 800, 45, 147)) ToggleGamePause(); // 开始/暂停
        if (CheckTouch(700, 800, 150, 300)) isReset = 1;       // 重新开始
        if (CheckTouch(700, 800, 302, 480)) {
            isExit = 1;
            break;
        }
    }
    return NULL;
}

// 切换游戏开始/暂停状态
void ToggleGamePause() {
    stopFlag = !stopFlag;
}

// 判断触摸是否在给定区域
int CheckTouch(int x1, int x2, int y1, int y2) {
    return (PI.Ts_x > x1 && PI.Ts_x < x2 && PI.Ts_y > y1 && PI.Ts_y < y2);
}

// 启动游戏模块
int StartGame() {
    if (GameInit() != 0) return -1;

    while (!isExit) {
        usleep(100000); // 主循环延时
    }

    pthread_cancel(PI.pid1);
    pthread_cancel(PI.pid2);

    ShowBmp(0, 0, "./rec/p_c.bmp");
    ShowBmp(250, 168, "./rec/GV.bmp");
    sleep(3); // 延时显示游戏结束画面
    GameFree();

    return 0;
}


void Game_Start(struct Lcd_Init * LCD,struct Touch_val * Touch,struct Filedir * GameFile,struct Filedir * SystemFile,
                    pthread_t Game_ball_pid,pthread_t Game_plate_pid,int * Control_Num){


                    }