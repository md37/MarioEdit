#pragma once

#include "classes/Tile.hpp"

class BackgroundTile : public Tile {

public:

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void setTransparency(sf::Uint8 transparency);

private:

    sf::Uint8 transparency = 255;

};
