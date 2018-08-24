#pragma once

#include "defines.hpp"
#include "classes/World/World.hpp"

class MushroomWorld : public World {

public:

    void drawBackground(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid) override;

protected:

    sf::Color backgroundColor = BG_LIGHT_COLOR;

    void drawHills(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, sf::Uint32 position);
    void drawHill(std::shared_ptr<sf::RenderWindow> window, sf::Int32 position, sf::Uint32 size);

    void drawClouds(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, sf::Uint32 position);
    void drawCloud(std::shared_ptr<sf::RenderWindow> window, sf::Vector2u position, sf::Uint32 size);
};
