#include "SceneGenerator.hpp"

#include "classes/Scene/Figure/Bush.hpp"
#include "classes/Scene/Figure/Cloud.hpp"
#include "classes/Scene/Figure/Hill.hpp"
#include "classes/Scene/SceneRegistry.hpp"

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
    auto bush = std::make_shared<Bush>(tileFactory, grid, sf::Vector2i(2, 2), 3);
    SceneRegistry::registerFigure(bush);
}

void SceneGenerator::createClouds() {
    auto cloud = std::make_shared<Cloud>(tileFactory, grid, sf::Vector2i(6, 10), 3);
    SceneRegistry::registerFigure(cloud);
}

void SceneGenerator::createHills() {
    auto hill = std::make_shared<Hill>(tileFactory, grid, sf::Vector2i(7, 2), 2);
    SceneRegistry::registerFigure(hill);
}

void SceneGenerator::generateForeground() {
    auto stone = tileFactory->createDynamicTile(0, 0);
    stone->addEventHandler(DynamicTile::MouseEnter, [](DynamicTile *tile) {
        tile->mouseEnter();
    });
    stone->addEventHandler(DynamicTile::MouseLeave, [](DynamicTile *tile) {
        tile->mouseLeave();
    });
    stone->addEventHandler(DynamicTile::StartDrag, [](DynamicTile *tile) {
        tile->startDrag();
    });
    stone->addEventHandler(DynamicTile::Drag, [](DynamicTile *tile) {
        tile->drag();
    });
    stone->addEventHandler(DynamicTile::Drop, [](DynamicTile *tile) {
        tile->drop();
    });

    stone->setGrid(grid);
    stone->snapToGrid(sf::Vector2u(2, 5));

    auto brick = tileFactory->createDynamicTile(5, 0);
    brick->addEventHandler(DynamicTile::MouseEnter, [](DynamicTile *tile) {
        tile->mouseEnter();
    });
    brick->addEventHandler(DynamicTile::MouseLeave, [](DynamicTile *tile) {
        tile->mouseLeave();
    });
    brick->addEventHandler(DynamicTile::StartDrag, [](DynamicTile *tile) {
        tile->startDrag();
    });
    brick->addEventHandler(DynamicTile::Drag, [](DynamicTile *tile) {
        tile->drag();
    });
    brick->addEventHandler(DynamicTile::Drop, [](DynamicTile *tile) {
        tile->drop();
    });

    brick->setGrid(grid);
    brick->snapToGrid(sf::Vector2u(5, 5));

    auto stair = tileFactory->createDynamicTile(2, 2);
    stair->addEventHandler(DynamicTile::MouseEnter, [](DynamicTile *tile) {
        tile->mouseEnter();
    });
    stair->addEventHandler(DynamicTile::MouseLeave, [](DynamicTile *tile) {
        tile->mouseLeave();
    });
    stair->addEventHandler(DynamicTile::StartDrag, [](DynamicTile *tile) {
        tile->startDrag();
    });
    stair->addEventHandler(DynamicTile::Drag, [](DynamicTile *tile) {
        tile->drag();
    });
    stair->addEventHandler(DynamicTile::Drop, [](DynamicTile *tile) {
        tile->drop();
    });

    stair->setGrid(grid);
    stair->snapToGrid(sf::Vector2u(8, 5));

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

    questionMark->isBlinking = true;
    questionMark->setGrid(grid);
    questionMark->snapToGrid(sf::Vector2u(11, 5));
}
