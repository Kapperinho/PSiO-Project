#pragma once

#include <SFML/Graphics.hpp>
#include "entity.h"

class Wall : public Entity
{
public:
    Wall(int x, int y, sf::Texture* texture);
};
