#pragma once
#include <conio.h>
#include "welcome.h"
#include "ship.h"
#include "bullet.h"
#include "pipe.h"

#define EASY 10
#define NORMAL 5
#define HARD 0

struct Logic
{
    int mode;
    
    bool checkWin = true; 
    bool distanceScore = true;
    bool shoot = false;
    bool gameOver = false;

    void controller(Ship &ship, int &bulletCount)
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

    void check_collision(int rows, Ship &ship, vector<Pipe> &pipes)
    {
        for (vector<float> ship_coord : ship.ship_coords)
        {
            for (int i = 0; i < pipes.size(); ++i)
            {
                for (vector<int> pipe_coord : pipes[i].pipe_coords)
                {
                    if ((ship_coord[0] == pipe_coord[0] && ship_coord[1] == pipe_coord[1]) || (ship_coord[0] == 0 || ship_coord[1] == 1 || ship_coord[1] == rows - 1))
                        gameOver = true;
                }
            }
        }
    }

    void check_bullet_collision(vector<Bullet> &bullets, vector<Pipe> &pipes, int columns)
    {
        for (int i = 0; i < pipes.size(); ++i)
        {
            for (vector<int> pipe_coord : pipes[i].pipe_coords)
            {
                if (bullets[0].bulletX + 2 == pipe_coord[0] || bullets[0].bulletX == columns)
                {
                    pipes[i]._delete(pipes);
                    bullets[0]._delete();
                    pipes.erase(pipes.begin() + i);
                    bullets.pop_back();
                    shoot = false;
                }
            }
        }
    }

    void check_win(Ship ship, int columns, int rows)
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

    void set_mode()
    {
        if (easyMode)
            mode = EASY;
        else if (normalMode)
            mode = NORMAL;
        else if (hardMode)
            mode = HARD;
        else if (wanderMode)
        {
            mode = EASY + 10;
            checkWin = false;
            distanceScore = false;
        }
    }
};