#pragma once
#include <cmath>
#include <iostream>
#include <conio.h>
#include <vector>
#include <time.h>
#include "utils.h"
#include "welcome.h"
using namespace std;

struct Ship
{
    vector<vector<float>> ship_coords;
    float shipX, shipY, shipSpeed;
    bool isEnemy;

    Ship(float shipX, float shipY, bool isEnemy = false)
        : shipX(shipX)
        , shipY(shipY)
        , isEnemy(isEnemy)
        , shipSpeed(isEnemy ? 0.2 : 2)
    {
    }

    void init()
    {
        draw();
        set_ship_coords();
    }

    void draw()
    {
        if (isEnemy)
        {
            gotoxy(shipX, shipY);
            cout << "_____";
            gotoxy(shipX, shipY + 1);
            cout << "|__\\<:";
        }
        else
        {
            gotoxy(shipX, shipY);
            cout << "_____";
            gotoxy(shipX, shipY + 1);
            cout << ":</__|";
        }
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

    void move(int rows)
    {
        static bool isUp = true;
        static int count = 1;
        static int changeDir = rand() % 50 + 40;

        if (round(shipY) == 3 || round(shipY + 1) == rows - 2 || count % changeDir == 0){
            isUp = isUp ? false : true;

            changeDir = rand() % 50 + 40;
        }
        
        if (!isUp)
        {
            _delete();
            shipY -= shipSpeed;
            draw();
        }

        else if (isUp)
        {
            _delete();
            shipY += shipSpeed;
            draw();
        }
        
        ++count;
    }
};
