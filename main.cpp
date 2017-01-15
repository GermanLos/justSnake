#include <iostream>
#include <world.h>

using namespace std;

int main(int argc, char *argv[])
{
    world w(' ');

    do
    {
        w.display();
        w.step();
        if(!w.snake.checkAlive())
            break;
    }while(true);
    
    // изменения в файле для создания нового коммита)
    return 0;
}
