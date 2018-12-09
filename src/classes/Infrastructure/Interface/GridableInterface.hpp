#pragma once

#include "classes/Editor/Scene/Grid.hpp"

class GridableInterface {

public:

    virtual void snapToGrid() = 0;
    virtual void snapToGrid(sf::Vector2i pointOnGrid) = 0;

};