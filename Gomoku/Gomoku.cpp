 #include "Gomoku.h"
#include <conio.h>

void Gomoku::GameRun()
{
	Init();
	Draw();
    Input();
    Update();
    Reset();

}

void Gomoku::Init()
{

	GameState = 0;
	cursorX = WIDTH/2;
	cursorY = HEIGHT/2;
	cursorLZ = 9;
	w_MoveTimes = 0;
	b_MoveTimes = 0;
	w_WinTimes = 0;
	b_WinTimes = 0;
	BLACK = boardTiles[9];
	WHITE = boardTiles[10];

    // 假设SIZE为棋盘上交叉点的数量,初始化map
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            int index = y * WIDTH + x;
            if (x == 0 && y == 0)
            {
                Map[index] = boardTiles[1]; // 左上角 '┏'
            }
            else if (x == 0 && y == HEIGHT - 1)
            {
                Map[index] = boardTiles[3]; // 左下角 '┗'
            }
            else if (x == WIDTH - 1 && y == 0)
            {
                Map[index] = boardTiles[2]; // 右上角 '┓'
            }
            else if (x == WIDTH - 1 && y == HEIGHT - 1)
            {
                Map[index] = boardTiles[4]; // 右下角 '┛'
            }
            else if (y == 0)
            {
                Map[index] = boardTiles[5]; // 上边界 '┳'
            }
            else if (y == HEIGHT - 1)
            {
                Map[index] = boardTiles[6]; // 下边界 '┻'
            }
            else if (x == 0)
            {
                Map[index] = boardTiles[7]; // 左边界 '┣'
            }
            else if (x == WIDTH - 1)
            {
                Map[index] = boardTiles[8]; // 右边界 '┫'
            }
            else
            {
                Map[index] = boardTiles[0]; // 交叉点 '╋'
            }
        }
    }

}



void Gomoku::Draw()
{
    system("cls");

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            int index = y * WIDTH + x;
            wcout << Map[index];
        }
        wcout << endl;
    }

    Sleep(30);
}

bool Gomoku::Input()
{
    char key = _getch(); // 获取玩家输入的键
    bool validInput = false;
    int pos;

    switch (key)
    {
        // 键盘输入来移动光标
    case 'w': // 向上移动
        if (cursorY > 0) cursorY--;
        break;
    case 's': // 向下移动
        if (cursorY < HEIGHT - 1) cursorY++;
        break;
    case 'a': // 向左移动
        if (cursorX > 0) cursorX--;
        break;
    case 'd': // 向右移动
        if (cursorX < WIDTH - 1) cursorX++;
        break;
    case 'k': // 落子
        pos = cursorY * WIDTH + cursorX;
        // 确保落子点为空，并且根据当前状态下黑棋或白棋
        if (Map[pos] == boardTiles[0] && (GameState % 2 == 0 ? b_MoveTimes <= w_MoveTimes : w_MoveTimes < b_MoveTimes))
        {
            Map[pos] = (GameState % 2 == 0) ? boardTiles[10] : boardTiles[9]; // '●' 黑棋, '○' 白棋
            GameState++;
            validInput = true;
        }
        break;
    case 'r': // 重置游戏
        if (Reset())
        {
            Init(); // 重置游戏应重新初始化棋盘
            validInput = true;
        }
        break;
    default:
        break;
    }

    return validInput; // 返回是否为有效输入
}


void Gomoku::Update()
{
    // 检查游戏是否有人获胜
    bool win = false;
    const int DX[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    const int DY[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    for (int i = 0; i < 8; ++i)
    {
        int count = 1; // 至少有1个棋子（当前刚下的棋子）
        // 向8个方向之一延伸检查相连的相同棋子数量
        for (int j = 1; j < 5; ++j)
        {
            int x = cursorX + DX[i] * j;
            int y = cursorY + DY[i] * j;

            // 超出棋盘的情况
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
                break;

            // 检查[X,Y]位置的棋子是否与当前下的棋子相同，如果相同count++
            if (Map[y * WIDTH + x] == Map[cursorY * WIDTH + cursorX])
                count++;
            else
                break;

            // 一旦count达到5，则赢得游戏
            if (count >= 5)
            {
                win = true;  
                break;
            }
        }

        if (win)
        {
            GameState = GameState % 2 == 0 ? -1 : -2; // -1表示黑棋赢，-2表示白棋赢
            break;
        }
    }
}

bool Gomoku::Reset()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Map[y * WIDTH + x] = boardTiles[0]; // 假设 boardTiles[0] 是空位的表示符
        }
    }

    GameState = 0;
    cursorX = WIDTH / 2;
    cursorY = HEIGHT / 2;
    cursorLZ = 9;
    w_MoveTimes = 0;
    b_MoveTimes = 0;
    w_WinTimes = 0;
    b_WinTimes = 0;
    BLACK = boardTiles[9];
    WHITE = boardTiles[10];

    return 1;
}
