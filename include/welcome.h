#pragma once
#include "utils.h"
#include <iostream>
using namespace std;

bool easyMode, normalMode, hardMode, wanderMode;

void sleepOnce(int &count, int sleep = 100)
{
    if (count == 0)
        Sleep(sleep);
}

bool welcome()
{
    static int count = 0;
    static int i = -3;

    hideCursor();

    int columns, rows;
    getConsoleSize(columns, rows);

    gotoxy((columns / 2) - 35, (rows / 2) - 11);
    sleepOnce(count);
    cout << " __      __                    .___";

    gotoxy((columns / 2) - 35, (rows / 2) - 10);
    sleepOnce(count);
    cout << "/  \\    /  \\_____    ____    __| _/___________";

    gotoxy((columns / 2) - 35, (rows / 2) - 9);
    sleepOnce(count);
    cout << "\\   \\/\\/   /\\__  \\  /    \\  / __ |/ __ \\_  __ \\";

    gotoxy((columns / 2) - 35, (rows / 2) - 8);
    sleepOnce(count);
    cout << " \\        /  / __ \\|   |  \\/ /_/ \\  ___/|  | \\/";

    gotoxy((columns / 2) - 35, (rows / 2) - 7);
    sleepOnce(count);
    cout << "  \\__/\\  /  (____  /___|  /\\____ |\\___  >__|";

    gotoxy((columns / 2) - 35, (rows / 2) - 6);
    sleepOnce(count);
    cout << "       \\/        \\/     \\/      \\/    \\/  ";

    sleepOnce(count, 500);
    gotoxy((columns / 2) - 20, (rows / 2) - 3);
    cout << "E A S Y  M O D E";
    gotoxy((columns / 2) - 20, (rows / 2) - 1);
    cout << "N O R M A L  M O D E";
    gotoxy((columns / 2) - 20, (rows / 2) + 1);
    cout << "H A R D  M O D E";
    gotoxy((columns / 2) - 20, (rows / 2) + 3);
    cout << "W A N D E R  M O D E";

    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
            gotoxy((columns / 2) - 24, (rows / 2) + i);
            cout << "  ";

            if (i != -3)
                i -= 2;

            break;
        case 's':
            gotoxy((columns / 2) - 24, (rows / 2) + i);
            cout << "  ";

            if (i != 3)
                i += 2;

            break;
        case 13:
            if (i == -3)
                easyMode = true;
            else if (i == -1)
                normalMode = true;
            else if (i == 1)
                hardMode = true;
            else
                wanderMode = true;

            return false;

        case 'q':
            exit(0);
        }
    }

    gotoxy((columns / 2) - 24, (rows / 2) + i);
    cout << ">>";

    sleepOnce(count, 300);
    gotoxy((columns / 2) - 35, (rows / 2) + 7);
    cout << "     S T A R T : [ENTER]      Q U I T : [Q]     ";

    ++count;

    return true;
}