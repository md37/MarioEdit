#pragma once

#include "classes/Infrastructure/TileFactory.hpp"
#include "classes/Editor/Object/StaticTile.hpp"
#include "classes/Editor/Scene/Grid/Grid.hpp"

class AbstractFigureGenerator {

public:

    AbstractFigureGenerator(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid);

    virtual std::vector<std::shared_ptr<StaticTile>> generate(sf::Vector2i pointOnGrid, sf::Uint8 size) = 0;

    void updateGrid(std::shared_ptr<Grid> grid);

protected:

    std::unique_ptr<TileFactory> &tileFactory;
    std::shared_ptr<Grid> grid;

};