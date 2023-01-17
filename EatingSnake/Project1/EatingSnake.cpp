#include <easyx.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define NODE_WIDTH 40

//  �ڵ�
typedef struct {
    int x;
    int y;
}node;

//  ��������
//  ����(0, y), (800, y)   0 <= y <= 600
//  ����(x, 0),(x, 600)    0 <= x <= 800
void paintGrid()
{
    //  ����
    for (int y = 0; y < 600; y += NODE_WIDTH)
    {
        line(0, y, 800, y);
    }
    //  ����
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
        //  ���Ͻǣ�������x���� * ������, ����y���� * �����ȡ�
        left = snake[i].x * NODE_WIDTH;
        top = snake[i].y * NODE_WIDTH;
        //  ���½ǣ���(����x���� + 1) * ������, (����y���� + 1) * �����ȡ�
        right = (snake[i].x + 1) * NODE_WIDTH;
        bottom = (snake[i].y + 1) * NODE_WIDTH;
        //  ͨ�����Ͻ������½�������ƾ���
        solidrectangle(left, top, right, bottom);
    }
}

//  ����ö��
enum direction
{
    eUp,
    eDown,
    eLeft,
    eRight
};


//  �������ƶ�
node snakeMove(node* snake, int length, int direction)
{
    //for (int i = 0; i < length; i++)
    //    printf("(%d, %d)\n", snake[i].x, snake[i].y);

    //  ��¼β�ڵ�
    node tail = snake[length - 1];

    //  ��β��㿪ʼ��ǰһ���ڵ㸲�Ǻ�һ���ڵ�
    //  0 1 2 3 4      0 1 2 3 4
    //  E D C B A ---> E E D C B
    for (int i = length - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    //  ��һ��ͷ�ڵ�
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

    //  ����ͷ�ڵ�
    //  E D C B A ---> F E D C B
    snake[0] = newHead;

    //for (int i = 0; i < length; i++)
    //    printf("(%d, %d)\n", snake[i].x, snake[i].y);

    //  ����β�ڵ�
    return tail;
}

//  ��������ı�direction
void changeDirection(enum direction* pD)
{
    //  ������뻺�������Ƿ�������
    if (_kbhit() != 0)
    {
        //  _getch������ȡ���뻺�����е�����
        char c = _getch();
        //  �ж����벢ת��
        switch (c)
        {
        case 'w':
            //  �����ƶ�
            if (*pD != eDown)
                *pD = eUp;
            break;
        case 's':
            //  �����ƶ�
            if (*pD != eUp)
                *pD = eDown;
            break;
        case 'a':
            //  �����ƶ�
            if (*pD != eRight)
                *pD = eLeft;
            break;
        case 'd':
            //  �����ƶ�
            if (*pD != eLeft)
                *pD = eRight;
            break;
        }
    }
}

//  ����ʳ��
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


//  �������ʳ��
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
    //  �Ƿ�ײǽ
    if (snake[0].x < 0 || snake[0].x > 800 / NODE_WIDTH)
        return true;

    if (snake[0].y < 0 || snake[0].y > 600 / NODE_WIDTH)
        return true;

    //  �Ƿ�Ե�����
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
    //  ���ñ���ɫ
    setbkcolor(RGB(164, 225, 202));
    //  ʹ�ñ���ɫ��մ���
    cleardevice();

    //  �߽ڵ�����
    node snake[100] = { {5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7} };
    //  �߽ڵ㳤��
    int length = 5;
    enum direction d = eRight;

    //  ʳ��
    srand(unsigned int(time(NULL)));
    node food = createFood(snake, length);

    while (1)
    {
        //  �����������
        cleardevice();
        //  ��������
        paintGrid();
        //  �����߽ڵ�
        paintSnake(snake, length);
        //  ����ʳ��
        paintFood(food);
        //  ����500ms
        Sleep(500);
        //  ��ȡ�������벢������洢������d
        changeDirection(&d);

        node lastTail = snakeMove(snake, length, d);
        //  �µ���ͷ�ڵ��Ƿ���ʳ��ڵ��غ�
        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            //  ����snake�ڵ���󳤶�
            if (length < 100)
            {
                //  �Ѿ��Ե�ʳ��, ����+1
                snake[length] = lastTail;
                length++;
            }
            //  ���������µ�ʳ��
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

        //  ��Ϸ�Ƿ����
        if (isGameOver(snake, length) == true)
        {
            //  ��Ϸ��������λ���ã���������ʳ��
            reset(snake, &length, &d);
            food = createFood(snake, length);
        }
    }

    getchar();
    closegraph();
    return 0;
}