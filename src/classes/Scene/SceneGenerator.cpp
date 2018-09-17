#include "SceneGenerator.hpp"

#include "classes/Scene/Figure/Bush.hpp"
#include "classes/Scene/Figure/Cloud.hpp"
#include "classes/Scene/Figure/Hill.hpp"
#include "classes/ObjectRegistry.hpp"

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
    ObjectRegistry::registerFigure(bush);
}

void SceneGenerator::createClouds() {
    auto cloud = std::make_shared<Cloud>(tileFactory, grid, sf::Vector2i(6, 9), 3);
    ObjectRegistry::registerFigure(cloud);
}

void SceneGenerator::createHills() {
    auto hill = std::make_shared<Hill>(tileFactory, grid, sf::Vector2i(7, 2), 2);
    ObjectRegistry::registerFigure(hill);
}

void SceneGenerator::generateForeground() {
    auto stone = tileFactory->createDynamicTile(0, 0);
    stone->setGrid(grid);
    stone->snapToGrid(sf::Vector2u(2, 5));

    auto brick = tileFactory->createDynamicTile(5, 0);
    brick->setGrid(grid);
    brick->snapToGrid(sf::Vector2u(5, 5));

    auto stair = tileFactory->createDynamicTile(2, 2);
    stair->setGrid(grid);
    stair->snapToGrid(sf::Vector2u(8, 5));

    auto questionMark = tileFactory->createDynamicTile(0, 11);
    questionMark->isBlinking = true;
    questionMark->setGrid(grid);
    questionMark->snapToGrid(sf::Vector2u(11, 5));
}
