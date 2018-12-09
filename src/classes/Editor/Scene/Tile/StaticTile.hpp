#pragma once

#include "classes/Editor/Scene/Tile/GridTile.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"

class StaticTile : public GridTile, public DrawableInterface {

public:

    StaticTile(sf::Sprite sprite, std::unique_ptr<Grid>& grid, TileConfig config);
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;
};
