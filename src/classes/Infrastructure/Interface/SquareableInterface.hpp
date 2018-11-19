#pragma once

#include <SFML/System/Vector2.hpp>

class SquareableInterface {

public:

    virtual sf::Vector2f getPosition()=0;
    virtual sf::Vector2u getSize()=0;

};