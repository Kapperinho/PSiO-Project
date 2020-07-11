#include "fruit.h"
#include "config.h"

Fruit::Fruit()
{
    setSize(sf::Vector2f(SIZE, SIZE));
    setFillColor(sf::Color::Red);
    setOutlineThickness(1);
    setOutlineColor(sf::Color::White);
}
