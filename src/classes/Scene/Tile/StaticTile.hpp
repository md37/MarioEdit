#pragma once

#include "GridTile.hpp"
#include "classes/Interface/DrawableInterface.hpp"

class StaticTile : public GridTile, public DrawableInterface {

public:

    StaticTile(sf::Sprite sprite, TileConfig config);
    void draw(std::shared_ptr<sf::RenderWindow> window) override;
};
