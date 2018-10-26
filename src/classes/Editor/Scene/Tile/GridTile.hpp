#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Scene/Grid.hpp"
#include "classes/System/Interface/GridableInterface.hpp"
#include "classes/System/Interface/LocatableOnGridInterface.hpp"

class GridTile : public Tile, GridableInterface, LocatableOnGridInterface {

public:

    explicit GridTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void setGrid(std::shared_ptr<Grid> grid) override;
    void snapToGrid() override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;

    sf::Vector2i getPointOnGrid() override;
    sf::Vector2u getSizeOnGrid() override;

    bool isOnIncompletePoint(sf::Vector2i pointOnGrid);

protected:

    std::shared_ptr<Grid> grid;
    sf::Vector2i pointOnGrid;

};
