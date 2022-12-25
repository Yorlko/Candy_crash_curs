#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>
#include "structCandy.hpp"
#include "move.hpp"

void mouse_click(int &click, int &x0, int &y0, int tile_size, sf::Vector2i pos, bool &isSwap, int &x, int &y, candy map[][10]){
    if (click == 1)
    {
      x0 = pos.x / tile_size + 1;
      y0 = pos.y / tile_size + 1;
    }
    if (click == 2)
    {
        x = pos.x / tile_size + 1;
        y = pos.y / tile_size + 1;
        if (abs(x - x0)+ abs(y - y0) == 1)
        {
            swap(map[y0][x0], map[y][x], map); isSwap = 1; click = 0;
        }
        else click = 1;
    }
}