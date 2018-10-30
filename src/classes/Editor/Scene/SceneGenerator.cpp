#include "SceneGenerator.hpp"

#include "classes/Editor/Scene/Figure/Bush.hpp"
#include "classes/Editor/Scene/Figure/Cloud.hpp"
#include "classes/Editor/Scene/Figure/Hill.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

SceneGenerator::SceneGenerator(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid): tileFactory(tileFactory) {
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
    auto bush = std::make_shared<Bush>(tileFactory, grid, 3);
    bush->snapToGrid(sf::Vector2i(2, 9));
    ObjectRegistry::registerFigure(bush);
}

void SceneGenerator::createClouds() {
    auto cloud = std::make_shared<Cloud>(tileFactory, grid, 3);
    cloud->snapToGrid(sf::Vector2i(6, 3));
    ObjectRegistry::registerFigure(cloud);
}

void SceneGenerator::createHills() {
    auto hill = std::make_shared<Hill>(tileFactory, grid, 2);
    hill->snapToGrid(sf::Vector2i(7, 7));
    ObjectRegistry::registerFigure(hill);
}