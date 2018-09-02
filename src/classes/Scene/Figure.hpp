#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Grid.hpp"
#include "classes/Scene/Tile/TileFactory.hpp"

class Figure {

public:

    Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position);

    void snapToGrid();

    virtual void draw(std::shared_ptr<sf::RenderWindow> window);

protected:

    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Grid> grid;

    sf::Vector2i position;
    std::vector<std::shared_ptr<GridTile>> tiles;

};
