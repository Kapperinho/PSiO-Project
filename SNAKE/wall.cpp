#include "wall.h"
#include "config.h"

Wall::Wall(int x, int y, sf::Texture* texture)
{
    x_ = x;
    y_ = y;
    setTexture(texture);
    setSize(sf::Vector2f(SIZE, SIZE));
    setActualPos();
}
