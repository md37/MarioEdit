#pragma once

#include "GridTile.hpp"

class StaticTile : public GridTile {

public:

    StaticTile(sf::Sprite sprite, TileConfig config);
    void draw(std::shared_ptr<sf::RenderWindow> window);
};
