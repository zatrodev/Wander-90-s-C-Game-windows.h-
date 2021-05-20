#include <time.h>
#include "utils.h"
#include "ship.h"
#include "pipe.h"
#include "welcome.h"
#include "bullet.h"
#include "logic.h"

#define PIPE_GAP 4
#define PIPE_SPAWN 40
#define BULLET_ADD 150
using namespace std;

void setup(int &columns, int &rows, float &shipX, float &shipY)
{
    hideCursor();

    getConsoleSize(columns, rows);

    system("cls");

    shipX = 3;
    shipY = (rows - 2) / 2;

    if (wanderMode)
        shipX = columns / 3;
}

void layout(int width, int height)
{
    gotoxy(0, 1);
    for (int i = 0; i <= width - 2; ++i)
        cout << "#";

    gotoxy(0, height - 1);
    for (int i = 0; i <= width - 2; ++i)
        cout << "#";

    for (int i = 1; i < height; ++i)
    {
        gotoxy(0, i);
        cout << "|";

        gotoxy(width - 1, i);
        cout << "|";
    }
}

void pipe_setup(int columns, int rows, float &topHeight, float &botHeight, float &pipeX, float &pipeY, int &color)
{
    srand(time(NULL));

    topHeight = rand() % (rows - 12) + 5;
    botHeight = (rows - 1) - topHeight - PIPE_GAP;
    pipeX = columns - (columns / 5);
    pipeY = rows - 2;
    color += 16;

    if (color == 256)
        color += 16;

    if (wanderMode)
        botHeight = (rows - 1) - topHeight - PIPE_GAP - 3;
}

void score(int score, int rows, Logic &logic, vector<Pipe> &vec_pipes, Ship ship, int &bulletCount)
{
    gotoxy(0, rows);

    if (logic.distanceScore)
        cout << "Score: " << score;
    else
    {
        static int point = 0;
        for (int i = 0; i < vec_pipes.size(); ++i)
        {
            if (ship.shipX == vec_pipes[i].pipeX || ship.shipY == vec_pipes[i].pipeY)
            {
                cout << "Score: " << ++point;

                if (point % 2 == 0 && point != 0)
                    ++bulletCount;
            }
        }
    }
}

int main()
{
    system("cls");
    while (welcome())
        ;

    Logic logic;

    logic.set_mode();

    int columns, rows;

    vector<Pipe> vec_pipes;
    vector<Bullet> bullets;

    int bulletCount = 0, color = 0, count = 0;

    float shipX, shipY;
    float topHeight, botHeight, pipeX, pipeY;

    setup(columns, rows, shipX, shipY);
    layout(columns, rows);

    Ship ship(shipX, shipY);
    while (!logic.gameOver)
    {
        logic.controller(ship, bulletCount);
        ship.init();

        if (logic.shoot)
        {
            if (bullets.size() == 0)
                bullets.push_back(Bullet(ship.shipX, ship.shipY));

            bullets[0].move();
            logic.check_bullet_collision(bullets, vec_pipes, columns);
        }

        if (count % BULLET_ADD == 0 && count != 0 && !wanderMode)
            ++bulletCount;

        if (count % PIPE_SPAWN == 0)
        {
            pipe_setup(columns, rows, topHeight, botHeight, pipeX, pipeY, color);
            vec_pipes.push_back(Pipe(topHeight, botHeight, pipeX, pipeY, color));
        }

        if (vec_pipes.size() != 0)
        {
            for (int i = 0; i < vec_pipes.size(); ++i)
                vec_pipes[i].move(vec_pipes);

            logic.check_collision(rows, ship, vec_pipes);
            score(count, rows, logic, vec_pipes, ship, bulletCount);
        }

        Bullet::print(bulletCount);

        if (logic.checkWin)
            logic.check_win(ship, columns, rows);

        Sleep(logic.mode);
        ++count;
    }
    
    gotoxy((columns / 2) - 10, rows / 2);
    cout << "G A M E  O V E R";

    gotoxy(10, rows);

    return 0;
}
