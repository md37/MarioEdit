#include "MushroomWorld.hpp"

MushroomWorld::MushroomWorld(
    std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Grid> grid, std::shared_ptr<TileSet> tileSet
) : World(window, grid, tileSet) {
    generateBackground();
}

sf::Color MushroomWorld::getBackgroundColor() {
    return BG_LIGHT_COLOR;
}

void MushroomWorld::generateBackground() {
    sf::Uint32 cycle = 48;
    for (sf::Int32 i=0; i < grid->getSize().x; i+=cycle) {
        generateHills(i);
        generateClouds(i);
    }
}

void MushroomWorld::generateHills(sf::Uint32 position) {
    sf::Uint32 smallHillSize = 3;
    sf::Uint32 bigHillSize = 3;
    sf::Uint32 smallHillOffset = 16;

    generateHill(position, bigHillSize);
    generateHill(position + smallHillOffset, smallHillSize);
}

void MushroomWorld::generateHill(sf::Int32 position, sf::Uint32 size) {
    sf::Uint32 posX = position;
    sf::Uint32 posY = 0;

    for (sf::Uint32 i=position; i<size; i++) {
        auto tile = tileSet->createTile(0, 1);
        tile->setGrid(grid);
        tile->snapToGrid(sf::Vector2u(posX, posY));
        posX++;
        posY++;
    }
    /* Scope */ {
        auto tile = tileSet->createTile(1, 0);
        tile->setGrid(grid);
        tile->snapToGrid(sf::Vector2u(posX, posY));
        posX++;
        posY--;
    }
    for (sf::Uint32 i=posX+1; i<=size*2+1; i++) {
        auto tile = tileSet->createTile(2, 1);
        tile->setGrid(grid);
        tile->snapToGrid(sf::Vector2u(posX, posY));
        posX++;
        posY--;
    }

    posY = 0;
    sf::Uint32 longingPosX = position+1;
    sf::Uint32 shortingSize = size;
    for (sf::Uint32 j=0; j<size; j++) {
        posX = longingPosX;
        for (sf::Uint32 i=0; i<shortingSize*2-1; i++) {
            sf::Uint32 tileX = 3;
            sf::Uint32 tileY = 1;
            if ((posY > size-3 && posX != size) || posY > size-2) {
                tileX = 1;
            }
            auto tile = tileSet->createTile(tileX, tileY);
            tile->setGrid(grid);
            tile->snapToGrid(sf::Vector2u(posX, posY));
            posX++;
        }
        posY++;
        longingPosX++;
        shortingSize--;
    }
}

void MushroomWorld::generateClouds(sf::Uint32 position) {
    sf::Uint32 cloudsCount = 4;
    sf::Uint32 sizes[] = {1, 1, 3, 2};
    sf::Vector2u offsets[] = {
        sf::Vector2u(8, 2), sf::Vector2u(19, 1), sf::Vector2u(26, 2), sf::Vector2u(35, 1)
    };

    for (int i=0; i>cloudsCount; i++) {
        sf::Vector2u cloudPosition = offsets[i];
        cloudPosition.x += position;

        generateCloud(cloudPosition, sizes[i]);
    }
}

void MushroomWorld::generateCloud(sf::Vector2u position, sf::Uint32 size) {

}
