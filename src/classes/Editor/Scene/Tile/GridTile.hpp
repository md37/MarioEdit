#pragma once

#include "classes/Editor/Tile.hpp"

class GridTile : public Tile {

public:

    explicit GridTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void setGrid(std::shared_ptr<Grid> grid);
    void snapToGrid();
    void snapToGrid(sf::Vector2u gridPosition);

    bool isOnIncompletePlace(sf::Vector2u dropPlace);

protected:

    std::shared_ptr<Grid> grid;
    sf::Vector2u gridPosition;

};
