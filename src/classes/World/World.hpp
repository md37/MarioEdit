#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/TileSet.hpp"
#include "classes/Grid.hpp"

class World {

public:

    World(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, std::shared_ptr<TileSet> tileSet);

    virtual sf::Color getBackgroundColor()=0;

protected:

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Grid> grid;
    std::shared_ptr<TileSet> tileSet;

};