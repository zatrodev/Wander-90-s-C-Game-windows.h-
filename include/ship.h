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
        ship_coords.clear();
        vector<float> subCoord;
        for (int i = 0; i <= 5; ++i){
            if (i == 5) {
                subCoord = {shipX + i, shipY + 1};
                ship_coords.push_back(subCoord);
            }
            else {
                subCoord = {shipX + i, shipY};
                ship_coords.push_back(subCoord);

                subCoord[1]++;
                ship_coords.push_back(subCoord);
            }
        }
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
        srand(time(NULL));
        static bool isUp = true;
        static int changeDir = isUp ? rand() % int(shipY) + 2 : rand() % (rows - 2 - int(shipY)) + shipY;

        if (round(shipY - 1) == changeDir || round(shipY) == changeDir || round(shipY + 1) == changeDir){
            isUp = isUp ? false : true;

            changeDir = isUp ? rand() % int(shipY) + 2 : rand() % (rows - 2 - int(shipY)) + shipY;
        }
        
        if (!isUp)
        {
            _delete();
            shipY += shipSpeed;
            draw();
        }

        else if (isUp)
        {
            _delete();
            shipY -= shipSpeed;
            draw();
        }
    }
};
