#pragma once

#include "classes/Editor/Object/GridTile.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"

class StaticTile : public GridTile, DrawableInterface {

public:

    StaticTile(sf::Sprite sprite, std::shared_ptr<Grid>& grid, TileConfig config);

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;
};
