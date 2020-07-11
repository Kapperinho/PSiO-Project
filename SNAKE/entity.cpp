#include "entity.h"
#include "config.h"

void Entity::setCoordinates(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Entity::setX(int x)
{
    x_ = x;
}

void Entity::setY(int y)
{
    y_ = y;
}

int Entity::getX() const
{
    return x_;
}

int Entity::getY() const
{
    return y_;
}

void Entity::setActualPos()
{
    setPosition(x_ * SIZE, y_ * SIZE);
}
