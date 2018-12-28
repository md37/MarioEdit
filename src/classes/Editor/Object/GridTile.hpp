#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Object/AbstractTile.hpp"
#include "classes/Editor/Scene/Grid/Grid.hpp"
#include "classes/Infrastructure/Interface/GridableInterface.hpp"
#include "classes/Infrastructure/Interface/SquareableOnGridInterface.hpp"

class GridTile : public AbstractTile, GridableInterface, SquareableOnGridInterface {

public:

    explicit GridTile(sf::Sprite sprite, std::shared_ptr<Grid>& grid, TileConfig config=TileConfig());

    void snapToGrid() override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;

    sf::Vector2i getPointOnGrid() const override;
    sf::Vector2u getSizeOnGrid() const override;

    bool isOnIncompletePoint(sf::Vector2i pointOnGrid) const;

protected:

    std::shared_ptr<Grid>& grid;
    sf::Vector2i pointOnGrid;

};
