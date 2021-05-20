#pragma once
#include <iostream>
#include "utils.h"
using namespace std;

struct Bullet
{
    int bulletSpeed = 2;
    int bulletX, bulletY;

    Bullet(int shipX, int shipY)
        : bulletX(shipX + 4)
        , bulletY(shipY + 1)
    {
        draw();
    }

    void draw()
    {
        gotoxy(bulletX, bulletY);
        cout << "[|>";
    }

    void _delete()
    {
        gotoxy(bulletX, bulletY);
        cout << "   ";
    }

    void move()
    {
        _delete();
        bulletX += bulletSpeed;
        draw();
    }

    static void print(int bulletCount)
    {
        gotoxy(2, 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "[|>"
             << " x" << bulletCount;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
};
