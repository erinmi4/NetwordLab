#include "ev.h"
#include "bmp.h"
#include "game.h"

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 12
#define TILE_SIZE 40
#define WIN_CONDITION 5

int flag = 0;
unsigned int Game_buf[BOARD_HEIGHT][BOARD_WIDTH] = {0};

// 游戏区块映射到棋盘位置
int Game_Change(int x, int y)
{
    int i = (x + TILE_SIZE / 2) / TILE_SIZE;
    int j = (y + TILE_SIZE / 2) / TILE_SIZE;

    // 边界检查
    if (i >= 0 && i < BOARD_WIDTH && j >= 0 && j < BOARD_HEIGHT)
    {
        if (Game_buf[j][i] == 0)
        {
            Game_buf[j][i] = flag ? 1 : 2;
            Dis_zi(j * TILE_SIZE, i * TILE_SIZE, flag);
            flag = 1 - flag;
        }
    }
    return 0;
}

// 清除棋盘
void clear(void)
{
    for (int a = 0; a < BOARD_HEIGHT; a++)
    {
        for (int b = 0; b < BOARD_WIDTH; b++)
        {
            Game_buf[a][b] = 0;
        }
    }
}

// 显示棋子
void Dis_zi(int x, int y, int flag)
{
    unsigned int color = flag ? 0x000000 : 0x00ffffff;
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= 330)
            {
                Display(color, j, i);
            }
        }
    }
}

// 判断游戏是否结束
void Game_Over(void)
{
    for (int a = 0; a < BOARD_HEIGHT; a++)
    {
        for (int b = 0; b < BOARD_WIDTH; b++)
        {
            if (Game_buf[a][b] != 0)
            {
                int count_h = 1, count_v = 1, count_d1 = 1, count_d2 = 1;

                // 横向检查
                for (int h = 1; h < WIN_CONDITION && a + h < BOARD_HEIGHT; h++)
                {
                    if (Game_buf[a][b] == Game_buf[a + h][b]) count_h++;
                    else break;
                }
                // 纵向检查
                for (int v = 1; v < WIN_CONDITION && b + v < BOARD_WIDTH; v++)
                {
                    if (Game_buf[a][b] == Game_buf[a][b + v]) count_v++;
                    else break;
                }
                // 对角线检查（左上到右下）
                for (int d1 = 1; d1 < WIN_CONDITION && a + d1 < BOARD_HEIGHT && b + d1 < BOARD_WIDTH; d1++)
                {
                    if (Game_buf[a][b] == Game_buf[a + d1][b + d1]) count_d1++;
                    else break;
                }
                // 对角线检查（右上到左下）
                for (int d2 = 1; d2 < WIN_CONDITION && a + d2 < BOARD_HEIGHT && b - d2 >= 0; d2++)
                {
                    if (Game_buf[a][b] == Game_buf[a + d2][b - d2]) count_d2++;
                    else break;
                }

                // 判断是否达到胜利条件
                if (count_h >= WIN_CONDITION || count_v >= WIN_CONDITION || count_d1 >= WIN_CONDITION || count_d2 >= WIN_CONDITION)
                {
                    Dis_pic("/game/bucuoo.bmp"); // 显示胜利图片
                    clear(); // 清除棋盘
                    return;
                }
            }
        }
    }
}
