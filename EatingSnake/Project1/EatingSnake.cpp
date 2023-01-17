#include <easyx.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define NODE_WIDTH 40

//  节点
typedef struct {
    int x;
    int y;
}node;

//  绘制网格
//  横线(0, y), (800, y)   0 <= y <= 600
//  竖线(x, 0),(x, 600)    0 <= x <= 800
void paintGrid()
{
    //  横线
    for (int y = 0; y < 600; y += NODE_WIDTH)
    {
        line(0, y, 800, y);
    }
    //  竖线
    for (int x = 0; x < 800; x += NODE_WIDTH)
    {
        line(x, 0, x, 600);
    }
}

void paintSnake(node* snake, int n)
{
    int left, top, right, bottom;
    for (int i = 0; i < n; i++)
    {
        //  左上角：【网格x坐标 * 网格宽度, 网格y坐标 * 网格宽度】
        left = snake[i].x * NODE_WIDTH;
        top = snake[i].y * NODE_WIDTH;
        //  右下角：【(网格x坐标 + 1) * 网格宽度, (网格y坐标 + 1) * 网格宽度】
        right = (snake[i].x + 1) * NODE_WIDTH;
        bottom = (snake[i].y + 1) * NODE_WIDTH;
        //  通过左上角与右下角坐标绘制矩形
        solidrectangle(left, top, right, bottom);
    }
}

//  方向枚举
enum direction
{
    eUp,
    eDown,
    eLeft,
    eRight
};


//  蛇身体移动
node snakeMove(node* snake, int length, int direction)
{
    //for (int i = 0; i < length; i++)
    //    printf("(%d, %d)\n", snake[i].x, snake[i].y);

    //  记录尾节点
    node tail = snake[length - 1];

    //  从尾结点开始，前一个节点覆盖后一个节点
    //  0 1 2 3 4      0 1 2 3 4
    //  E D C B A ---> E E D C B
    for (int i = length - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    //  下一个头节点
    node newHead;
    newHead = snake[0];
    if (direction == eUp)
    {
        newHead.y--;
    }
    else if (direction == eDown)
    {
        newHead.y++;
    }
    else if (direction == eLeft)
    {
        newHead.x--;
    }
    else //  right
    {
        newHead.x++;
    }

    //  更新头节点
    //  E D C B A ---> F E D C B
    snake[0] = newHead;

    //for (int i = 0; i < length; i++)
    //    printf("(%d, %d)\n", snake[i].x, snake[i].y);

    //  返回尾节点
    return tail;
}

//  键盘输入改变direction
void changeDirection(enum direction* pD)
{
    //  检查输入缓存区中是否有数据
    if (_kbhit() != 0)
    {
        //  _getch函数获取输入缓存区中的数据
        char c = _getch();
        //  判断输入并转向
        switch (c)
        {
        case 'w':
            //  向上移动
            if (*pD != eDown)
                *pD = eUp;
            break;
        case 's':
            //  向下移动
            if (*pD != eUp)
                *pD = eDown;
            break;
        case 'a':
            //  向左移动
            if (*pD != eRight)
                *pD = eLeft;
            break;
        case 'd':
            //  向右移动
            if (*pD != eLeft)
                *pD = eRight;
            break;
        }
    }
}

//  绘制食物
/*
(x * NODE_WIDTH, y * NODE_WIDTH)
@-----------
|          |
|          |
|          |
|          |
|          |
-----------@ ((x + 1) * NODE_WIDTH, (y + 1) * NODE_WIDTH)
*/
void paintFood(node food)
{
    int left, top, right, bottom;
    left = food.x * NODE_WIDTH;
    top = food.y * NODE_WIDTH;
    right = (food.x + 1) * NODE_WIDTH;
    bottom = (food.y + 1) * NODE_WIDTH;
    setfillcolor(YELLOW);
    solidrectangle(left, top, right, bottom);
    setfillcolor(WHITE);
}


//  随机创建食物
node createFood(node* snake, int length)
{
    node food;
    while (1)
    {
        food.x = rand() % (800 / NODE_WIDTH);
        food.y = rand() % (600 / NODE_WIDTH);

        int i;
        for (i = 0; i < length; i++)
        {
            if (snake[i].x == food.x && snake[i].y == food.y)
            {
                break;
            }
        }
        if (i < length)
            continue;
        else
            break;
    }
    return food;
}

bool isGameOver(node* snake, int length)
{
    //  是否撞墙
    if (snake[0].x < 0 || snake[0].x > 800 / NODE_WIDTH)
        return true;

    if (snake[0].y < 0 || snake[0].y > 600 / NODE_WIDTH)
        return true;

    //  是否吃到蛇身
    for (int i = 1; i < length; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return true;
    }
    return false;
}

void reset(node* snake, int* pLength, enum direction* d)
{
    snake[0] = node{ 5, 7 };
    snake[1] = node{ 4, 7 };
    snake[2] = node{ 3, 7 };
    snake[3] = node{ 2, 7 };
    snake[4] = node{ 1, 7 };
    *pLength = 5;
    *d = eRight;
}

int main()
{
    initgraph(800, 600);
    //  设置背景色
    setbkcolor(RGB(164, 225, 202));
    //  使用背景色清空窗体
    cleardevice();

    //  蛇节点坐标
    node snake[100] = { {5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7} };
    //  蛇节点长度
    int length = 5;
    enum direction d = eRight;

    //  食物
    srand(unsigned int(time(NULL)));
    node food = createFood(snake, length);

    while (1)
    {
        //  清空整个窗体
        cleardevice();
        //  绘制网格
        paintGrid();
        //  绘制蛇节点
        paintSnake(snake, length);
        //  绘制食物
        paintFood(food);
        //  休眠500ms
        Sleep(500);
        //  获取键盘输入并将方向存储到变量d
        changeDirection(&d);

        node lastTail = snakeMove(snake, length, d);
        //  新的蛇头节点是否与食物节点重合
        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            //  限制snake节点最大长度
            if (length < 100)
            {
                //  已经吃到食物, 长度+1
                snake[length] = lastTail;
                length++;
            }
            //  重新生成新的食物
            food = createFood(snake, length);
        }

    }
    
    while (1)
    {
        cleardevice();
        paintGrid();
        paintSnake(snake, length);
        paintFood(food);
        Sleep(500);
        changeDirection(&d);
        node lastTail = snakeMove(snake, length, d);
        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            if (length < 100)
            {
                snake[length] = lastTail;
                length++;
            }
            food = createFood(snake, length);
        }

        //  游戏是否结束
        if (isGameOver(snake, length) == true)
        {
            //  游戏结束，复位设置，重新生成食物
            reset(snake, &length, &d);
            food = createFood(snake, length);
        }
    }

    getchar();
    closegraph();
    return 0;
}