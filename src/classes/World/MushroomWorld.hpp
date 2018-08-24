#pragma once

#include "defines.hpp"
#include "classes/World/World.hpp"

class MushroomWorld : public World {

public:

    MushroomWorld(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, std::shared_ptr<TileSet> tileSet);
    virtual sf::Color getBackgroundColor() override;

protected:

    sf::Color backgroundColor = BG_LIGHT_COLOR;

    void generateBackground();
    void generateHills(sf::Uint32 position);
    void generateHill(sf::Int32 position, sf::Uint32 size);

    void generateClouds(sf::Uint32 position);
    void generateCloud(sf::Vector2u position, sf::Uint32 size);
};
