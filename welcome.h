#pragma once
#include "utils.h"
#include <iostream>
using namespace std;

bool easyMode, normalMode, hardMode, wanderMode;

bool welcome()
{
    static int i = -1;

    hideCursor();

    int columns, rows;
    getConsoleSize(columns, rows);

    gotoxy((columns / 2) - 35, (rows / 2) - 9);
    cout << " __      __                    .___";

    gotoxy((columns / 2) - 35, (rows / 2) - 8);
    cout << "/  \\    /  \\_____    ____    __| _/___________";

    gotoxy((columns / 2) - 35, (rows / 2) - 7);
    cout << "\\   \\/\\/   /\\__  \\  /    \\  / __ |/ __ \\_  __ \\";

    gotoxy((columns / 2) - 35, (rows / 2) - 6);
    cout << " \\        /  / __ \\|   |  \\/ /_/ \\  ___/|  | \\/";

    gotoxy((columns / 2) - 35, (rows / 2) - 5);
    cout << "  \\__/\\  /  (____  /___|  /\\____ |\\___  >__|";

    gotoxy((columns / 2) - 35, (rows / 2) - 4);
    cout << "       \\/        \\/     \\/      \\/    \\/  ";

    gotoxy((columns / 2) - 18, (rows / 2) - 1);
    cout << "E A S Y  M O D E";
    gotoxy((columns / 2) - 18, (rows / 2) + 1);
    cout << "N O R M A L  M O D E";
    gotoxy((columns / 2) - 18, (rows / 2) + 3);
    cout << "H A R D  M O D E";
    gotoxy((columns / 2) - 18, (rows / 2) + 5);
    cout << "W A N D E R  M O D E";

    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
            gotoxy((columns / 2) - 22, (rows / 2) + i);
            cout << "  ";

            if (i != -1)
                i -= 2;

            break;
        case 's':
            gotoxy((columns / 2) - 22, (rows / 2) + i);
            cout << "  ";

            if (i != 5)
                i += 2;

            break;
        case 13:
            if (i == -1)
                easyMode = true;
            else if (i == 1)
                normalMode = true;
            else if (i == 3)
                hardMode = true;
            else
                wanderMode = true;

            return false;
        }
    }

    gotoxy((columns / 2) - 22, (rows / 2) + i);
    cout << ">>";

    gotoxy((columns / 2) - 20, (rows / 2) + 9);
    cout << "Press [ENTER] to Start";

    return true;
}
