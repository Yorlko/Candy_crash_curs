#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "mouseClickHandler.hpp"
#include "structCandy.hpp"
#include "generationCandys.hpp"
#include "checkCombinations.hpp"
#include "move.hpp"

using namespace sf;

struct candy map[10][10];

int main()
{
    srand(time(nullptr));

    RenderWindow window(VideoMode(1280, 720), "Candy Crush");
    window.setFramerateLimit(60);

    Texture bg_texture, candys_texture, button_texture;
    bg_texture.loadFromFile("images/background.png");
    candys_texture.loadFromFile("images/candys.png");
    button_texture.loadFromFile("images/button_bg.png");

    Sprite background(bg_texture), candys(candys_texture), button_bg(button_texture);
    button_bg.setPosition(490, 150);

    Font font_regular, font_black;
    font_regular.loadFromFile("fonts/Inter-Regular.ttf");
    font_black.loadFromFile("fonts/Inter-Black.ttf");

    Text points_text("0", font_regular, 20);
    points_text.setPosition(10, 5);
    Text rating_text("", font_regular, 28);
    rating_text.setPosition(500, 260);
    Text newgame_button_text("NEW GAME", font_black, 48);
    newgame_button_text.setPosition(500, 160);
    Text endgame_button_text("END GAME", font_black, 24);
    endgame_button_text.setPosition(1110, 655);

    generation(map);

    int x0, y0, x, y;
    int click = 0;
    Vector2i position;
    bool isSwap = false;
    bool isMoving = false;
    int points = 0;
    int scene = 0;

    if (std::filesystem::exists("last_game.data"))
    {
        std::ifstream points_file("last_game.data");
        points_file >> points;
        points_file.close();
    }

    std::vector<int> rating;
    for(int i = 0; i < 5; i++) rating.push_back(0);
    if (std::filesystem::exists("rating.data"))
    {
        std::ifstream rating_file("rating.data");
        rating_file >> rating[0] >> rating[1] >> rating[2] >> rating[3] >> rating[4];
        rating_file.close();
    }

    String rating_str;
    for(int i = 0; i < 5; i++) rating_str += std::to_string(i + 1) + " - " + std::to_string(rating[i]) + " points\n";
    rating_text.setString(rating_str);

    if (points > 0) { newgame_button_text.setString("CONTINUE"); newgame_button_text.setPosition(510, 160); }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                std::ofstream points_file("last_game.data");
                points_file << points;
                points_file.close();

                std::ofstream rating_file("rating.data");
                rating_file << rating[0] << " " << rating[1] << " " << rating[2] << " " << rating[3] << " " << rating[4];
                rating_file.close();

                window.close();
            }

            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                {
                    if (scene == 0)
                    {
                        position = Mouse::getPosition(window);
                        if (position.x >= 490 && position.x <= 790 && position.y >= 150 & position.y <= 230)
                        {
                            scene = 1;
                            button_bg.setScale(0.5f, 0.5f);
                            button_bg.setPosition(1100, 650);
                        }
                    }
                    else if (scene == 1)
                    {
                        position = Mouse::getPosition(window);
                        if (position.x >= 1100 && position.x <= 1250 && position.y >= 650 & position.y <= 690)
                        {
                            if (points > rating[4]) rating[4] = points;
                            std::sort(rating.begin(), rating.end(), std::greater<int>());

                            rating_str = "";
                            for(int i = 0; i < 5; i++) rating_str += std::to_string(i + 1) + " - " + std::to_string(rating[i]) + " points\n";
                            rating_text.setString(rating_str);

                            scene = 0;
                            points = 0;

                            newgame_button_text.setString("NEW GAME");
                            newgame_button_text.setPosition(500, 160);

                            button_bg.setScale(1, 1);
                            button_bg.setPosition(490, 150);
                        }
                        if (!isSwap && !isMoving) click++;
                        position -= offset;
                    }
                }
         }

        if (scene == 0)
        {
            window.draw(background);
            window.draw(button_bg);
            window.draw(newgame_button_text);
            window.draw(rating_text);
        }
        else if (scene == 1)
        {
            mouse_click(click, x0, y0, tile_size, position, isSwap, x, y, map);
            check(map);
            move(isMoving, map);
            deleting(isMoving, map);
            antiswap(isMoving, isSwap, map, y0, x0, y, x);
            update(isMoving, map, points);

            window.draw(background);

            window.draw(button_bg);
            window.draw(endgame_button_text);

            points_text.setString("Points: " + std::to_string(points));
            window.draw(points_text);

            for (int i = 1;i <= 8;i++)
                for (int j = 1; j <= 8; j++)
                {
                    candy element = map[i][j];
                    candys.setTextureRect(IntRect(element.kind * 49, 0, 49, 49));
                    candys.setScale(70 / candys.getLocalBounds().height, 70 / candys.getLocalBounds().width);
                    candys.setColor(Color(255, 255, 255, element.alpha));
                    candys.setPosition(element.x, element.y);
                    candys.move(offset.x - tile_size, offset.y - tile_size);
                    window.draw(candys);
                }
        }

        window.display();
    }
    return 0;
}

