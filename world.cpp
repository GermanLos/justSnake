#include "world.h"

world::world()
{
    filler = '.';
    for(int i = 0; i < MAX_W; i++)
        for(int k = 0; k < MAX_H; k++)
            map[i][k] = filler;
    needGenBug = true;
}

world::world(char ch)
{
    filler = ch;
    for(int i = 0; i < MAX_W; i++)
        for(int k = 0; k < MAX_H; k++)
            map[i][k] = filler;
    needGenBug = true;
}

void world::display()
{
    system("cls");
    drawSnake();        // рисуем змейку

    if(needGenBug)
    {
        genTheBug();
        needGenBug = false;
    }
    // печатаем рамку
    for(int i = 0; i < MAX_W * 2 + 3; i++)
        cout << "#";
    cout << endl;

    // печатаем поле
    for(int i = 0; i < MAX_W; i++)
    {
        cout << "# ";
        for(int k = 0; k < MAX_H; k++)
            if(i != bugPosX || k != bugPosY)
                cout << map[i][k] << " ";
            else
                cout << "* ";
        cout << "#" << endl;
    }

    // снова рамку
    for(int i = 0; i < MAX_W * 2 + 3; i++)
        cout << "#";
}

void world::genTheBug()
{
    srand(time(NULL));

    bugPosX = rand() % 15;
    bugPosY = rand() % 15;
    map[bugPosX][bugPosY] = '*';
}

void world::drawSnake()
{
    for(int i = 0; i < MAX_W; i++)
        for(int k = 0; k < MAX_H; k++)
            map[i][k] = filler;

    // рисуем голову
    int coordX = snake.coord[0].x,
        coordY = snake.coord[0].y;
        map[coordX][coordY] = snake.head;

    // рисуем тело
    for(int i = 1; i < snake.size; i++)
    {
        coordX = snake.coord[i].x;
        coordY = snake.coord[i].y;
        map[coordX][coordY] = 'o';
    }
}

void world::step()
{
    if(GetAsyncKeyState(VK_LEFT) && snake.route != 3)
        snake.moveSnake(3);
    else if(GetAsyncKeyState(VK_UP) && snake.route != 0)
        snake.moveSnake(0);
    else if(GetAsyncKeyState(VK_RIGHT) && snake.route != 1)
        snake.moveSnake(1);
    else if(GetAsyncKeyState(VK_DOWN) && snake.route != 2)
        snake.moveSnake(2);
    else
        snake.moveSnake(snake.route);

    if(snake.coord[0].x == bugPosX && snake.coord[0].y == bugPosY)
    {
        needGenBug = true;
        snake.snakeUp(bugPosX, bugPosY);
    }
    Sleep(150);
}

Coordinates::Coordinates()
{

}

Coordinates::Coordinates(int c1, int c2)
{
    x = c1;
    y = c2;
}

Snake::Snake()
{
    size = 3;
    route = 1;
    coord.push_back(Coordinates(2, 2));
    coord.push_back(Coordinates(2, 1));
    coord.push_back(Coordinates(2, 0));
    head = '>';
}

void Snake::calcHeadRoute()
{
    switch(route)
    {
    case 0: head = '^'; break;
    case 1: head = '>'; break;
    case 2: head = 'V'; break;
    case 3: head = '<'; break;
    default: head = 'X'; break;

    }
}

bool Snake::checkAlive()
{
    // проверка на столкновения змейки самой собой
    for(int i = 1; i < size - 1; i++)
        if(coord[i].x == coord[0].x && coord[i].y == coord[0].y)
        {
            route = 4;
            calcHeadRoute();
            return false;
        }

    return true;
}

void Snake::moveSnake(int r1)
{
    Coordinates temp = coord[0];
    Coordinates temp2;
    route = r1;

    switch(route)
    {
        case 0:  coord[0].x--; break;
        case 1:  coord[0].y++; break;
        case 2:  coord[0].x++; break;
        case 3:  coord[0].y--; break;
        default: cout << "ERROR! Don't route snake in this side! ";
                 system("pause");
                 break;
    }

    for(int i = 1; i < size; i++)
    {
        temp2 = coord[i];
        coord[i] = temp;
        temp = temp2;
    }

    if(coord[0].x == MAX_W)
        coord[0].x -= MAX_W;
    if(coord[0].x < 0)
        coord[0].x = MAX_W;
    if(coord[0].y == MAX_H)
        coord[0].y -= MAX_H;
    if(coord[0].y < 0)
        coord[0].y = MAX_H;
    calcHeadRoute();
}

void Snake::snakeUp(int c1, int c2)
{
    coord.push_back(Coordinates(c1, c2));
    size++;
}

