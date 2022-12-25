#pragma once
#include "structCandy.hpp"
#include "move.hpp"

void check(candy map[][10])
{
    for(int i = 1;i <= 8;i++)
        for(int j = 1;j <= 8;j++)
        {
            if (map[i][j].kind == map[i+1][j].kind || map[i+1][j].kind > 4 || map[i][j].kind > 4)
            if (map[i][j].kind == map[i-1][j].kind || map[i-1][j].kind > 4 || map[i][j].kind > 4)
            if (map[i-1][j].kind == map[i+1][j].kind || map[i-1][j].kind > 4 || map[i+1][j].kind > 4)
            for(int k = -1; k <= 1; k++)
            {
                if (map[i + k][j].kind == 6) for(int n = 0; n <= 8; n++) map[i + k][n].combination++;
                if (map[i + k][j].kind == 5) for(int n = -1; n <= 1; n++) for(int m = -1; m <= 1; m++) if(i + k + n >= 0 && i + k + n <= 8 && j + m >= 0 && j + m <= 8) map[i + k + n][j + m].combination++;
                map[i + k][j].combination++;
            }

            if (map[i][j].kind == map[i][j+1].kind || map[i][j+1].kind > 4 || map[i][j].kind > 4)
            if (map[i][j].kind == map[i][j-1].kind || map[i][j-1].kind > 4 || map[i][j].kind > 4)
            if (map[i][j-1].kind == map[i][j+1].kind || map[i][j-1].kind > 4 || map[i][j+1].kind > 4)
            for(int k = -1; k <= 1; k++)
            {
                if (map[i][j + k].kind == 6) for(int n = 0; n <= 8; n++) map[i][n].combination++;
                if (map[i][j + k].kind == 5) for(int n = -1; n <= 1; n++) for(int m = -1; m <= 1; m++) if(i + n >= 0 && i + n <= 8 && j + k + m >= 0 && j + k + m <= 8) map[i + n][j + k + m].combination++;
                map[i][j + k].combination++;
            }
        }
}

void update(bool &isMoving, candy map[][10], int &points)
{
    if (!isMoving)
    {
        for(int i = 8;i > 0; i--)
        for(int j = 1;j <= 8;j++)
            if (map[i][j].combination)
            for(int n = i;n > 0; n--)
                if (!map[n][j].combination) {swap(map[n][j], map[i][j], map); break;};

        for(int j = 1; j <= 8;j++)
        for(int i = 8,n = 0; i > 0; i--)
            if (map[i][j].combination)
            {
                points++;
                map[i][j].kind = rand() % 5;
                if (rand() % 100 < 5) map[i][j].kind = 5 + rand() % 2;
                map[i][j].y = -tile_size * n++;
                map[i][j].combination=0;
                map[i][j].alpha = 255;
            }
    }
}