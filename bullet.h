#pragma once
#include "utils.h"
#include "ship.h"
#include "pipe.h"
using namespace std;

struct Bullet
{
    int bulletSpeed = 2;
    int bulletX, bulletY;

    Bullet(int shipX, int shipY) : bulletX(shipX + 4), bulletY(shipY) {
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
};