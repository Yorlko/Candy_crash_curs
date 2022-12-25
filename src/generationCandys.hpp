#pragma once
#include "structCandy.hpp"
void generation(candy map[][10]) 
{
    for (int i = 1;i <= 8; i++)
        for (int j = 1; j <= 8; j++)
        {
            map[i][j].kind = rand() % 5;
            map[i][j].column = j;
            map[i][j].row = i;
            map[i][j].x = j * tile_size;
            map[i][j].y = i * tile_size;
        }
}
