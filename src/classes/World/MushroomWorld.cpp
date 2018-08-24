#include "MushroomWorld.hpp"

void MushroomWorld::drawBackground(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid) {
    window->clear(BG_LIGHT_COLOR);

    sf::Uint32 cycle = 48;
    for (sf::Int32 i=0; i < grid->getSize().x; i+=cycle) {
        drawHills(window, grid, i);
        drawClouds(window, grid, i);
    }
}

void MushroomWorld::drawHills(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, sf::Uint32 position) {
    sf::Uint32 smallHillSize = 3;
    sf::Uint32 bigHillSize = 4;
    sf::Uint32 smallHillOffset = 16;

    drawHill(window, position, bigHillSize);
    drawHill(window, position+smallHillOffset, smallHillSize);
}

void MushroomWorld::drawHill(std::shared_ptr<sf::RenderWindow> window, sf::Int32 position, sf::Uint32 size) {

}

void MushroomWorld::drawClouds(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, sf::Uint32 position) {
    sf::Uint32 cloudsCount = 4;
    sf::Uint32 sizes[] = {1, 1, 3, 2};
    sf::Vector2u offsets[] = {
        sf::Vector2u(8, 2), sf::Vector2u(19, 1), sf::Vector2u(26, 2), sf::Vector2u(35, 1)
    };

    for (int i=0; i>cloudsCount; i++) {
        sf::Vector2u cloudPosition = offsets[i];
        cloudPosition.x += position;

        drawCloud(window, cloudPosition, sizes[i]);
    }
}

void MushroomWorld::drawCloud(std::shared_ptr<sf::RenderWindow> window, sf::Vector2u position, sf::Uint32 size) {

}
