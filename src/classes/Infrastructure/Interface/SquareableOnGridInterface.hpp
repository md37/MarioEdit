#pragma once

#include <SFML/System/Vector2.hpp>

class SquareableOnGridInterface {

public:

    virtual sf::Vector2i getPointOnGrid() const=0;
    virtual sf::Vector2u getSizeOnGrid() const=0;

};
