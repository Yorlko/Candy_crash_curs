#pragma once
#include <SFML/Graphics.hpp>
#include "structCandy.hpp"

void swap(candy first, candy second, candy map[][10])
{
  std::swap(first.column,second.column);
  std::swap(first.row,second.row);

  map[first.row][first.column] = first;
  map[second.row][second.column] = second;
}

void move(bool &isMoving, candy map[][10]) 
{
    isMoving=false;
    for (int i = 1;i <= 8;i++)
        for (int j = 1;j <= 8;j++)
        {
            candy &element = map[i][j];
            int dx, dy;
            for(int n = 0; n < 4; n++)
            {
                dx = element.x - element.column * tile_size;
                dy = element.y - element.row * tile_size;
                if (dx) element.x -= dx/abs(dx);
                if (dy) element.y -= dy/abs(dy);
            }
            if (dx||dy) isMoving = 1;
        }
}

void deleting(bool &isMoving, candy map[][10])
{
    if (!isMoving)
        for (int i = 1; i <= 8; i++)
            for (int j = 1;j <= 8; j++)
                if (map[i][j].combination) if (map[i][j].alpha>10) {map[i][j].alpha -= 10; isMoving=true;}
}

void antiswap(bool &isMoving, bool &isSwap, candy map[][10], int y0, int x0, int y, int x) 
{
    int score = 0;
    for (int i = 1;i <= 8;i++)
    for (int j = 1;j <= 8;j++)
        score += map[i][j].combination;
    if (isSwap && !isMoving) {if (!score) swap(map[y0][x0], map[y][x], map); isSwap=0;}
}