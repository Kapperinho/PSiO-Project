#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::RectangleShape
{
public:
    void setCoordinates(int x, int y);

    void setActualPos();

    void setX(int x);
    void setY(int y);

    int getX() const;
    int getY() const;
protected:
    int x_;
    int y_;
};
