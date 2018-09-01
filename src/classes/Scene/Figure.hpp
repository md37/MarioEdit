#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Grid.hpp"
#include "classes/Scene/Tile/TileFactory.hpp"

class Figure {

public:

    Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position);

    virtual void createTiles()=0;

protected:

    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Grid> grid;

    sf::Vector2i position;

};
