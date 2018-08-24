#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Grid.hpp"

class World {

public:

    virtual void drawBackground(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid)=0;

};