#include "snake.h"

#include "config.h"


Snake::Snake()
{
    x_ = 15;
    y_ = 6;

    setSize(sf::Vector2f(SIZE, SIZE));
    setFillColor(sf::Color::Green);
}

void Snake::setStartPos()
{
    x_ = 15;
    y_ = 6;
}
