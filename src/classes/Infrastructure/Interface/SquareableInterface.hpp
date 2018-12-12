#pragma once

#include <SFML/System/Vector2.hpp>

class SquareableInterface {

public:

    virtual sf::Vector2f getPosition() const=0;
    virtual sf::Vector2u getSize() const=0;

};
