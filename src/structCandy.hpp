#pragma once
#include <SFML/Graphics.hpp>

int tile_size = 80;
sf::Vector2i offset(320, 40);

struct candy
{
    int x, y;
    int column, row;
    int kind;
    int combination;
    int alpha;
    candy()
    {
      combination = 0; 
      alpha = 255;
    }
};