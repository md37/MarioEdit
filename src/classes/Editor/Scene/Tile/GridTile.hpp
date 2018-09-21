#pragma once

#include "classes/Editor/Tile.hpp"

class GridTile : public Tile {

public:

    explicit GridTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void setGrid(std::shared_ptr<Grid> grid);
    void snapToGrid();
    void snapToGrid(sf::Vector2u gridPosition);

    void snapToCenterPoint();
    bool isOnIncompletePlace();

protected:

    std::shared_ptr<Grid> grid;
    sf::Vector2u gridPosition;

};
