#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include "utils.h"
#include "welcome.h"
using namespace std;

struct Ship 
{
    vector<vector<float>> ship_coords;
    float shipX, shipY, shipSpeed = 2;

    Ship(float shipX, float shipY) 
        : shipX(shipX)
        , shipY(shipY)
    {
    }

    void init()
    {
        draw();
        set_ship_coords();
    }

    void draw()
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

    void _delete()
    {
        gotoxy(shipX, shipY);
        cout << "     ";
        gotoxy(shipX, shipY + 1);
        cout << "      ";
    }
};
