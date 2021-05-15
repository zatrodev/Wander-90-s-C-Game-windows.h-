#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Pipe
{
    vector <vector<float>> pipe_coords;
    float topHeight, botHeight;
    float pipeX, pipeY, pipeSpeed;

    Pipe(float topHeight, float botHeight, float pipeX, float pipeY, float pipeSpeed) : topHeight(topHeight), botHeight(botHeight), pipeX(pipeX), pipeY(pipeY), pipeSpeed(pipeSpeed)
    {
        draw_pipe();
    }

    void draw_pipe()
    {
        pipe_coords.clear();
        for (float i = 2; i < topHeight + 2; ++i)
        {
            gotoxy(pipeX, i);
            pipe_coords.push_back(vector<float>{pipeX, i});
            if (i == topHeight + 1)
                cout << "[_";
            else
                cout << "[";

            gotoxy(pipeX + 2, i);
            pipe_coords.push_back(vector<float>{pipeX + 2, i});
            cout << "]";
        }

        for (float i = pipeY; i >= pipeY - botHeight; --i)
        {
            if (i == pipeY - botHeight)
            {
                gotoxy(pipeX, i);
                pipe_coords.push_back(vector<float>{pipeX, i});
                pipe_coords.push_back(vector<float>{pipeX + 2, i});
                cout << "[^]";
            }
            else
            {
                gotoxy(pipeX, i);
                pipe_coords.push_back(vector<float>{pipeX, i});
                cout << "[";

                gotoxy(pipeX + 2, i);
                pipe_coords.push_back(vector<float>{pipeX + 2, i});
                cout << "]";
            }
        }
    }

    void delete_pipe(vector <Pipe> &vec_pipes)
    {
        for (vector<float> coords : pipe_coords)
        {
            gotoxy(coords[0], coords[1]);
            cout << "   ";
        }

        if (pipeX < 5)
            vec_pipes.erase(vec_pipes.begin());
    }

    void move(vector <Pipe> &vec_pipes)
    {
        delete_pipe(vec_pipes);
        pipeX -= pipeSpeed;
        draw_pipe();
    }
};
