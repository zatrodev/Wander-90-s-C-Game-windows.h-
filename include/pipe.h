#pragma once
#include <iostream>
#include <vector>
#include "utils.h"

#define PIPE_THRESHOLD 6
using namespace std;

struct Pipe
{
    vector<vector<int>> pipe_coords;

    int topHeight, botHeight, pipeSpeed = 1;
    int pipeX, pipeY;
    int color;

    Pipe(int topHeight, int botHeight, int pipeX, int pipeY, int color)
        : topHeight(topHeight)
        , botHeight(botHeight)
        , pipeX(pipeX)
        , pipeY(pipeY)
        , color(color)
    {
        draw();
    }

    void draw()
    {
        pipe_coords.clear();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        for (int i = 2; i < topHeight; ++i)
        {
            pipe_coords.push_back(vector<int>{pipeX, i});
            pipe_coords.push_back(vector<int>{pipeX + 2, i});
            if (i == topHeight - 1)
            {
                gotoxy(pipeX, i);
                pipe_coords.push_back(vector<int>{pipeX + 1, i});
                cout << "[_]";
            }
            else {
                gotoxy(pipeX, i);
                cout << "[";
                
                gotoxy(pipeX + 2, i);
                cout << "]";
            }
        }

        for (int i = 0; i < botHeight; ++i)
        {
            pipe_coords.push_back(vector<int>{pipeX, pipeY - i});
            pipe_coords.push_back(vector<int>{pipeX + 2, pipeY - i});
            if (i == botHeight - 1)
            {
                gotoxy(pipeX, pipeY - i);
                pipe_coords.push_back(vector<int>{pipeX + 1, pipeY - i});
                cout << "[^]";
            }
            else
            {
                gotoxy(pipeX, pipeY - i);
                cout << "[";

                gotoxy(pipeX + 2, pipeY - i);
                cout << "]";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }

    void _delete()
    {
        for (vector<int> coords : pipe_coords)
        {
            gotoxy(coords[0], coords[1]);
            cout << "  ";
        }
    }

    void move()
    {
        _delete();
        pipeX -= pipeSpeed;
        draw();
    }
};
