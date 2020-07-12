#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "snake.h"
#include "fruit.h"
#include "config.h"
#include "wall.h"

class Game
{
public:
    Game();

    void start();

private:
    void GameAction();
    void menu();

    Fruit apple_;
    Snake snake_[100];

    int snakeLength_ = 3;
    Kierunek dir_ = Kierunek::RIGHT;
    int points_ = 0;

    sf::RenderWindow window_;
    sf::Clock clock_;
    sf::RectangleShape block_;
    sf::Font font_;

    std::vector<Wall> map_;
    std::vector<sf::RectangleShape> hearts_;

    sf::Texture wallTexture_;
    sf::Texture backgroundTexture_;
    sf::Texture heartTexture_;
    sf::Texture titleTexture_;
};
