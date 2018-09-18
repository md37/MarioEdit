#pragma once

#include "classes/Editor/Tile.hpp"

class GridTile : public Tile {

public:

    explicit GridTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void setGrid(std::shared_ptr<Grid> grid);
    void snapToGrid();
    void snapToGrid(sf::Vector2u gridPosition);

    void snapToCenterPoint();
    void snapToWindowBound();

protected:

    bool isOnLeftEdge();
    bool isOnRightEdge();
    bool isOnTopEdge();
    bool isOnBottomEdge();

    bool isOnTopLeftCorner();
    bool isOnBottomLeftCorner();
    bool isOnBottomRightCorner();
    bool isOnTopRightCorner();

    void snapToLeftEdge();
    void snapToRightEdge();
    void snapToTopEdge();
    void snapToBottomEdge();

    void snapToTopLeftCorner();
    void snapToBottomLeftCorner();
    void snapToBottomRightCorner();
    void snapToTopRightCorner();

    std::shared_ptr<Grid> grid;
    sf::Vector2u gridPosition;

};
