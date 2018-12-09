#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Scene/Grid.hpp"
#include "classes/Infrastructure/Interface/GridableInterface.hpp"
#include "classes/Infrastructure/Interface/SquareableOnGridInterface.hpp"

class GridTile : public Tile, GridableInterface, SquareableOnGridInterface {

public:

    explicit GridTile(sf::Sprite sprite, std::unique_ptr<Grid>& grid, TileConfig config=TileConfig());

    void snapToGrid() override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;

    sf::Vector2i getPointOnGrid() override;
    sf::Vector2u getSizeOnGrid() override;

    bool isOnIncompletePoint(sf::Vector2i pointOnGrid) const;

protected:

    std::unique_ptr<Grid>& grid;
    sf::Vector2i pointOnGrid;

};
