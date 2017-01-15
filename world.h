#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h>
#include <dos.h>

const int MAX_W = 15;
const int MAX_H = 15;

using namespace std;

//--------------------класс Coordinates----------
struct Coordinates
{
    int x;
    int y;

    Coordinates();
    Coordinates(int, int);  // конструктор с двумя аргументами
};

//--------------------класс Snake----------------
class Snake
{
public:
    int size;
    vector<Coordinates> coord;
    int route;
    char head;

    explicit Snake();

    void calcHeadRoute();   // указать направление головы
    bool checkAlive();      // жива ли змейка
    void moveSnake(int r1); // передвижение змейки
    void snakeUp(int c1, int c2);// увеличивает рост змейки
};

//--------------------класс world----------------
class world
{
public:
    char map[MAX_W][MAX_H];
    char filler;
    int bugPosX;
    int bugPosY;
    bool needGenBug;
    Snake snake;

    explicit world();
    explicit world(char ch);

    void display();
    void genTheBug();
    void drawSnake();
    void step();
};





#endif // WORLD_H
