#pragma once
#include <iostream>
#include "utils.h"

#define BULLET_THRESHOLD 2
using namespace std;

struct Bullet
{
    int bulletSpeed = 2;
    int bulletX, bulletY;
    bool isEnemyBullet;

    Bullet(int shipX, int shipY, bool isEnemyBullet = false)
        : bulletX(isEnemyBullet ? shipX - 4 : shipX + 4)
        , bulletY(shipY + 1)
        , isEnemyBullet(isEnemyBullet)
        , bulletSpeed(isEnemyBullet ? -2 : 2)
    {
        draw();
    }

    void draw()
    {
        if (isEnemyBullet){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            gotoxy(bulletX, bulletY);
            cout << "<|]";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            gotoxy(bulletX, bulletY);
            cout << "[|>";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
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
