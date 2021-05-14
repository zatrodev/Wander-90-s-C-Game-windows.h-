#pragma once
#include "spaceship.h"
#include "utils.h"
using namespace std;

struct Pipe
{
    static vector <Pipe> vec_pipes;
    vector<vector<int>> pipe_coords;
    int topHeight, botHeight;
    int pipeX, pipeY;

    Pipe(int topHeight, int botHeight, int pipeX, int pipeY) : topHeight(topHeight), botHeight(botHeight), pipeX(pipeX), pipeY(pipeY)
    {
    }

    void init()
    {
        draw_pipe();
        move();
        set_pipe_coords();
        delete_pipe();
    }

    void draw_pipe()
    {
        for (int i = 2; i < topHeight + 2; ++i)
        {
            gotoxy(pipeX, i);
            pipe_coords.push_back(vector<int>{pipeX, i});
            if (i == topHeight + 1)
                cout << "[_";
            else
                cout << "[";

            gotoxy(pipeX + 2, i);
            pipe_coords.push_back(vector<int>{pipeX + 2, i});
            cout << "]";
        }

        for (int i = pipeY; i >= pipeY - botHeight; --i)
        {
            if (i == pipeY - botHeight)
            {
                gotoxy(pipeX, i);
                pipe_coords.push_back(vector<int>{pipeX, i});
                cout << "[^]";
            }
            else
            {
                gotoxy(pipeX, i);
                pipe_coords.push_back(vector<int>{pipeX, i});
                cout << "[";

                gotoxy(pipeX + 2, i);
                pipe_coords.push_back(vector<int>{pipeX + 2, i});
                cout << "]";
            }
        }
    }

    void delete_pipe()
    {
        if (pipeX < 5)
        {
            for (vector<int> coords : pipe_coords)
            {
                gotoxy(coords[0], coords[1]);
                cout << "";
            }

            vec_pipes.erase(vec_pipes.begin());
        }
    }


    void set_pipe_coords()
    {
        for (int i = 0; i < pipe_coords.size(); ++i)
            pipe_coords[i][0] -= 2;
    }

    void move()
    {
        pipeX -= 2;
    }
};