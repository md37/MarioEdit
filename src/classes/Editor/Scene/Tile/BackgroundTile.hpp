#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Object/Tile.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"

class BackgroundTile : public Tile, public DrawableInterface {

public:

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;
    void setTransparency(sf::Uint8 transparency);

private:

    sf::Uint8 transparency = 255;

};
