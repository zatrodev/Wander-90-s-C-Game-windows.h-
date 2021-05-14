#include <iostream>
#include <time.h>
#include "utils.h"
#include "spaceship.h"
#include "pipe.h"
using namespace std;

bool gameOver;
int columns, rows;

Ship ship;

vector<Pipe> Pipe::vec_pipes;
int topHeight, botHeight, pipeX, pipeY;

void setup()
{
    setWindowSize(500, 200);

    system("cls");

    getConsoleSize(columns, rows);
    ship.shipX = 5;
    ship.shipY = (rows - 2) / 2;

    gameOver = false;
}

void pipe_setup()
{
    srand(time(NULL));

    topHeight = rand() % (rows - 15) + 5;
    botHeight = (rows - 1) - topHeight - 7;
    pipeX = columns - 10;
    pipeY = rows - 2;
}

void score()
{
    static int score = 0;
    if (ship.shipX == Pipe::vec_pipes[0].pipeX || ship.shipX == Pipe::vec_pipes[0].pipeY)
    {
        gotoxy(0, rows);
        cout << "Score: " << ++score;
    }
}

void check_collision()
{
    for (vector<int> ship_coord : ship.ship_coords)
    {
        for (vector<int> pipe_coord : Pipe::vec_pipes[0].pipe_coords)
        {
            if ((ship_coord[0] == pipe_coord[0] && ship_coord[1] == pipe_coord[1]) || (ship_coord[0] == 0 || ship_coord[1] == 0 || ship_coord[1] == rows - 1))
                gameOver = true;
        }
    }
}

void layout()
{
    gotoxy(0, 1);
    for (int i = 0; i < columns; ++i)
        cout << "#";

    gotoxy(0, rows - 1);
    for (int i = 0; i < columns; ++i)
        cout << "#";

    for (int i = 2; i < (rows - 1); ++i)
    {

        string col_space = "";

        gotoxy(0, i);
        for (int j = 0; j < columns; ++j)
            col_space += " ";

        cout << col_space;
    }
}

int main()
{
    int count = 0;
    setup();
    while (!gameOver)
    {
        layout();
        ship.init();

        if (count % 30 == 0 || count == 0)
        {
            pipe_setup();
            Pipe::vec_pipes.push_back(Pipe(topHeight, botHeight, pipeX, pipeY));
        }

        for (int i = 0; i < Pipe::vec_pipes.size(); ++i)
            Pipe::vec_pipes[i].init();

        check_collision();
        score();

        Sleep(10);
        ++count;
    }

    return 0;
}