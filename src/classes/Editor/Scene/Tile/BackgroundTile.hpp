#pragma once

#include "classes/Editor/Tile.hpp"
#include "classes/System/Interface/DrawableInterface.hpp"

class BackgroundTile : public Tile, public DrawableInterface {

public:

    void draw(std::shared_ptr<sf::RenderWindow> window) override;
    void setTransparency(sf::Uint8 transparency);

private:

    sf::Uint8 transparency = 255;

};
