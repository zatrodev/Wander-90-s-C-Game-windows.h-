#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include "utils.h"
#include "pipe.h"
using namespace std;

struct Ship
{
    vector <vector <int>> ship_coords;
    int shipX, shipY;
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

    void set_ship_coords(){
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

    void ship_controller()
    {
        if (kbhit())
        {
            switch (getch())
            {
            case 'w':
                shipY -= 2;
                break;
            case 'a':
                shipX -= 6;
                break;
            case 's':
                shipY += 2;
                break;
            case 'd':
                shipX += 6;
                break;
            }
        }
    }
};