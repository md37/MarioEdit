#include "SceneGenerator.hpp"

#include "classes/Scene/Figure/Bush.hpp"
#include "classes/Scene/Figure/Cloud.hpp"
#include "classes/Scene/Figure/Hill.hpp"

SceneGenerator::SceneGenerator(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid) {
    this->tileFactory = tileFactory;
    this->grid = grid;
}

void SceneGenerator::generate() {
    generateBackground();
    generateForeground();
}

void SceneGenerator::generateBackground() {
    createBushes();
    createClouds();
    createHills();
}

void SceneGenerator::createBushes() {
    Bush bush(tileFactory, grid, sf::Vector2i(2, 2), 3);
    bush.createTiles();
}

void SceneGenerator::createClouds() {
    Cloud cloud(tileFactory, grid, sf::Vector2i(2, 8), 3);
    cloud.createTiles();
}

void SceneGenerator::createHills() {
    Hill hill(tileFactory, grid, sf::Vector2i(10, 0), sf::Vector2u(4, 4));
    hill.createTiles();
}

void SceneGenerator::generateForeground() {
    auto questionMark = tileFactory->createDynamicTile(0, 11);
    questionMark->addEventHandler(DynamicTile::MouseEnter, [](DynamicTile *tile) {
        tile->mouseEnter();
    });
    questionMark->addEventHandler(DynamicTile::MouseLeave, [](DynamicTile *tile) {
        tile->mouseLeave();
    });
    questionMark->addEventHandler(DynamicTile::StartDrag, [](DynamicTile *tile) {
        tile->changeImage(0, 11);
        tile->startDrag();
    });
    questionMark->addEventHandler(DynamicTile::Drag, [](DynamicTile *tile) {
        tile->drag();
    });
    questionMark->addEventHandler(DynamicTile::Drop, [](DynamicTile *tile) {
        tile->drop();
    });

    questionMark->setGrid(grid);
    questionMark->snapToGrid(sf::Vector2u(8, 5));
}
