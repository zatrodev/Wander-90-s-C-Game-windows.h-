#include <time.h>
#include "utils.h"
#include "ship.h"
#include "pipe.h"
#include "welcome.h"
#include "bullet.h"

#define PIPE_GAP 4
#define PIPE_SPAWN 40

#define BULLET_ADD 100
using namespace std;

void setup(int &columns, int &rows, float &shipX, float &shipY, bool &gameOver)
{
    hideCursor();

    getConsoleSize(columns, rows);
    system("cls");

    shipX = 3;
    shipY = (rows - 2) / 2;

    gameOver = false;

    if (wanderMode)
        shipX = 40;
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
        botHeight = (rows - 1) - topHeight - PIPE_GAP + 3;
}

void controller(Ship &ship, bool &shoot, int &bulletCount)
{
    if (wanderMode)
    {
        static int count = 0;
        ship.shipSpeed = 0.5;
        static bool isUp = true;

        if (kbhit())
        {
            switch (getch())
            {
            case 32:
                ++count;

                if (!isUp)
                    isUp = true;
                else
                    isUp = false;

                break;
            case 'p':
                if (bulletCount != 0 && !shoot)
                {
                    shoot = true;
                    --bulletCount;
                }

                break;
            }
        }

        if (!isUp && count != 0)
        {
            ship._delete();
            ship.shipY -= ship.shipSpeed;
            ship.draw();
        }

        else if (isUp && count != 0)
        {
            ship._delete();
            ship.shipY += ship.shipSpeed;
            ship.draw();
        }
    }

    else
    {
        if (kbhit())
        {
            switch (getch())
            {
            case 'w':
                ship._delete();
                ship.shipY -= ship.shipSpeed;
                ship.draw();
                break;
            case 'a':
                ship._delete();
                ship.shipX -= ship.shipSpeed + 4;
                ship.draw();
                break;
            case 's':
                ship._delete();
                ship.shipY += ship.shipSpeed;
                ship.draw();
                break;
            case 'd':
                ship._delete();
                ship.shipX += ship.shipSpeed + 4;
                ship.draw();
                break;
            case 'p':
                if (bulletCount != 0 && !shoot)
                {
                    shoot = true;
                    --bulletCount;
                }
            }
        }
    }
}

void score(int score, int rows, bool distance_score, vector<Pipe> &vec_pipes, Ship ship, int &bulletCount)
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
            {
                cout << "Score: " << ++point;

                if (point % 2 == 0 && point != 0)
                    ++bulletCount;
            }
        }
    }
}

void print_bullet(int &bulletCount)
{
    gotoxy(2, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "[|>"
         << " x" << bulletCount;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void check_collision(int rows, Ship &ship, vector<Pipe> &vec_pipes, bool &gameOver)
{
    for (vector<float> ship_coord : ship.ship_coords)
    {
        for (int i = 0; i < vec_pipes.size(); ++i)
        {
            for (vector<int> pipe_coord : vec_pipes[i].pipe_coords)
            {
                if ((ship_coord[0] == pipe_coord[0] && ship_coord[1] == pipe_coord[1]) || (ship_coord[0] == 0 || ship_coord[1] == 1 || ship_coord[1] == rows - 1))
                    gameOver = true;
            }
        }
    }
}

void check_bullet_collision(vector<Bullet> &bullets, vector<Pipe> &vec_pipes, bool &shoot)
{
    for (int i = 0; i < vec_pipes.size(); ++i)
    {
        for (vector<int> pipe_coord : vec_pipes[i].pipe_coords)
        {
            if (bullets[0].bulletX + 2 == pipe_coord[0])
            {
                vec_pipes[i]._delete(vec_pipes);
                bullets[0]._delete();
                vec_pipes.erase(vec_pipes.begin() + i);
                bullets.pop_back();
                shoot = false;
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

void set_mode(int &mode, bool &checkWin, bool &distance_score)
{
    if (easyMode)
        mode = 20;
    else if (normalMode)
        mode = 10;
    else if (hardMode)
        mode = 5;
    else if (wanderMode)
    {
        mode = 20;
        checkWin = false;
        distance_score = false;
    }
}

int main()
{
    system("cls");
    while (welcome())
        ;

    int mode;
    bool checkWin = true, distance_score = true;

    set_mode(mode, checkWin, distance_score);

    bool gameOver;
    int columns, rows;

    vector<Pipe> vec_pipes;
    vector<Bullet> bullets;

    int bulletCount = 0;
    float shipX, shipY;
    float topHeight, botHeight, pipeX, pipeY;
    int color = 0, count = 0;
    bool shoot = false;

    setup(columns, rows, shipX, shipY, gameOver);
    layout(columns, rows);

    Ship ship(shipX, shipY);
    while (!gameOver)
    {
        controller(ship, shoot, bulletCount);
        ship.init();

        if (shoot)
        {
            if (bullets.size() == 0)
                bullets.push_back(Bullet(ship.shipX, ship.shipY));

            bullets[0].move();
            check_bullet_collision(bullets, vec_pipes, shoot);
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

            check_collision(rows, ship, vec_pipes, gameOver);
            score(count, rows, distance_score, vec_pipes, ship, bulletCount);
        }

        print_bullet(bulletCount);

        if (checkWin)
            check_win(ship, columns, rows, gameOver);

        Sleep(mode);
        ++count;
    }

    return 0;
}
