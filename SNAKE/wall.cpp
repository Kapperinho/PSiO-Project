#include "wall.h"
#include "config.h"

Wall::Wall(int x, int y)
{
    x_ = x;
    y_ = y;
    setSize(sf::Vector2f(SIZE, SIZE));
    setFillColor(sf::Color::Yellow);
    setActualPos();
}
