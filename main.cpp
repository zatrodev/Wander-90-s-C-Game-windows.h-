#include <iostream>
#include <time.h>
#include <cmath>
#include "utils.h"
#include "ship.h"
#include "pipe.h"
#include "welcome.h"

using namespace std;

void setup(int &columns, int &rows, float &pipeSpeed, float &shipX, float &shipY, float &shipSpeed, bool &gameOver)
{
    hideCursor();

    setWindowSize(600, 200);
    getConsoleSize(columns, rows);

    system("cls");

    pipeSpeed = 1;
    shipSpeed = 2;
    shipX = pipeSpeed + 2;
    shipY = (rows - 2) / 2;

    gameOver = false;

    if (wanderMode)
        shipX = 40;
}

void layout(int width, int height)
{
    gotoxy(0, 1);
    for (int i = 0; i <= width; ++i)
        cout << "#";

    gotoxy(0, height - 1);
    for (int i = 0; i <= width; ++i)
        cout << "#";

    for (int i = 1; i < height; ++i)
    {
        gotoxy(0, i);
        cout << "|";

        gotoxy(width, i);
        cout << "|";
    }
}

void pipe_setup(int columns, int rows, float &topHeight, float &botHeight, float &pipeX, float &pipeY)
{
    srand(time(NULL));

    topHeight = rand() % (rows - 12) + 5;
    botHeight = (rows - 1) - topHeight - 6.5;
    pipeX = columns - 10;
    pipeY = rows - 2;

    if (wanderMode)
        botHeight = (rows - 1) - topHeight - 8;
}

void score(int score, int rows, bool distance_score, vector<Pipe> vec_pipes, Ship ship)
{
    gotoxy(0, rows);

    if (distance_score)
        cout << "Score: " << score;
    else
    {
        static int point = 0;
        for (int i = 0; i < vec_pipes.size(); ++i)
        {
            if (ship.shipX == vec_pipes[i].pipeX || ship.shipY == vec_pipes[i].pipeY)
                cout << "Score: " << ++point;
        }
    }
}

void check_collision(int rows, Ship ship, vector<Pipe> vec_pipes, bool &gameOver)
{
    for (vector<float> ship_coord : ship.ship_coords)
    {
        for (int i = 0; i < vec_pipes.size(); ++i)
        {
            for (vector<float> pipe_coord : vec_pipes[i].pipe_coords)
            {
                if ((ship_coord[0] == pipe_coord[0] && ship_coord[1] == pipe_coord[1]) || (ship_coord[0] == 0 || ship_coord[1] == 0 || ship_coord[1] == rows - 1))
                    gameOver = true;
            }
        }
    }
}

void check_win(Ship ship, int columns, int rows, bool &gameOver)
{
    for (vector<float> ship_coord : ship.ship_coords)
    {
        for (int i = 0; i < rows; ++i)
        {
            if (ship_coord[0] == columns && ship_coord[1] == i)
            {
                gameOver = true;
            }
        }
    }
}

int main()
{
    system("cls");
    while (welcome())
        ;

    int mode;
    bool checkWin = true, distance_score = true;

    if (easyMode)
        mode = 20;
    else if (normalMode)
        mode = 10;
    else if (hardMode)
        mode = 0;
    else if (wanderMode)
    {
        mode = 20;
        checkWin = false;
        distance_score = false;
    }

    bool gameOver;
    int columns, rows;

    vector<Pipe> vec_pipes;

    float shipX, shipY;
    float topHeight, botHeight, pipeX, pipeY, pipeSpeed, shipSpeed;
    int count = 0;

    setup(columns, rows, pipeSpeed, shipX, shipY, shipSpeed, gameOver);
    layout(columns, rows);

    Ship ship(shipX, shipY, shipSpeed);
    while (!gameOver)
    {
        ship.init();

        if (count % 40 == 0)
        {
            pipe_setup(columns, rows, topHeight, botHeight, pipeX, pipeY);
            vec_pipes.push_back(Pipe(topHeight, botHeight, pipeX, pipeY, pipeSpeed));
        }

        for (int i = 0; i < vec_pipes.size(); ++i)
            vec_pipes[i].move(vec_pipes);

        check_collision(rows, ship, vec_pipes, gameOver);
        score(count, rows, distance_score, vec_pipes, ship);

        if (checkWin)
            check_win(ship, columns, rows, gameOver);

        Sleep(mode);
        ++count;
    }

    return 0;
}
