#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include "utils.h"
#include "pipe.h"
#include "welcome.h"
using namespace std;

struct Ship
{
    vector<vector<float>> ship_coords;
    float shipX, shipY, shipSpeed;

    Ship(float shipX, float shipY, float shipSpeed) : shipX(shipX), shipY(shipY), shipSpeed(shipSpeed)
    {
        draw_ship();
    }

    void init()
    {
        draw_ship();
        set_ship_coords();
        ship_controller();
    }

    void draw_ship()
    {
        gotoxy(shipX, shipY);
        cout << "_____";
        gotoxy(shipX, shipY + 1);
        cout << ":</__|";
    }

    void set_ship_coords()
    {
        ship_coords = {
            {shipX, shipY},
            {shipX + 1, shipY},
            {shipX + 2, shipY},
            {shipX + 3, shipY},
            {shipX + 4, shipY},
            {shipX, shipY + 1},
            {shipX + 1, shipY + 1},
            {shipX + 2, shipY + 1},
            {shipX + 3, shipY + 1},
            {shipX + 4, shipY + 1},
            {shipX + 5, shipY + 1},
        };
    }

    void delete_ship()
    {
        gotoxy(shipX, shipY);
        cout << "     ";
        gotoxy(shipX, shipY + 1);
        cout << "      ";
    }

    void ship_controller()
    {
        if (wanderMode)
        {
            static int count = 0;
            shipSpeed = 0.5;
            static bool isUp = true;

            if (kbhit()){
                if (getch() == 32){
                    ++count;

                    if (!isUp)
                        isUp = true;
                    else
                        isUp = false;
                }
            }
            
            if (!isUp && count != 0){
                delete_ship();
                shipY -= shipSpeed;
                draw_ship();
            }

            else  if (isUp && count != 0) {
                delete_ship();
                shipY += shipSpeed;
                draw_ship();
            }
        }

        else
        {
            if (kbhit())
            {
                switch (getch())
                {
                case 'w':
                    delete_ship();
                    shipY -= shipSpeed;
                    draw_ship();
                    break;
                case 'a':
                    delete_ship();
                    shipX -= shipSpeed + 4;
                    draw_ship();
                    break;
                case 's':
                    delete_ship();
                    shipY += shipSpeed;
                    draw_ship();
                    break;
                case 'd':
                    delete_ship();
                    shipX += shipSpeed + 4;
                    draw_ship();
                    break;
                }
            }
        }
    }
};