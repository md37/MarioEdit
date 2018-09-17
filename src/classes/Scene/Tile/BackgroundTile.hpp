#pragma once

#include "classes/Tile.hpp"
#include "classes/Interface/DrawableInterface.hpp"

class BackgroundTile : public Tile, public DrawableInterface {

public:

    void draw(std::shared_ptr<sf::RenderWindow> window) override;
    void setTransparency(sf::Uint8 transparency);

private:

    sf::Uint8 transparency = 255;

};
