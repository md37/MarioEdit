#include "SceneGenerator.hpp"

#include "classes/Editor/Scene/Figure/Bush.hpp"
#include "classes/Editor/Scene/Figure/Cloud.hpp"
#include "classes/Editor/Scene/Figure/Hill.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

SceneGenerator::SceneGenerator(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid) {
    this->tileFactory = tileFactory;
    this->grid = grid;
}

void SceneGenerator::generate() {
    generateBackground();
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