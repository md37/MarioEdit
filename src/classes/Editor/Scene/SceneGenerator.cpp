#include "SceneGenerator.hpp"

#include "classes/Editor/Scene/Figure/Bush.hpp"
#include "classes/Editor/Scene/Figure/Cloud.hpp"
#include "classes/Editor/Scene/Figure/Hill.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

SceneGenerator::SceneGenerator(std::unique_ptr<TileFactory> &tileFactory, std::unique_ptr<Grid>& grid): tileFactory(tileFactory), grid(grid) {

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
    auto bush = std::make_shared<Bush>(tileFactory, grid, 1);
    bush->snapToGrid(sf::Vector2i(2, 9));
    ObjectRegistry::add(bush);
}

void SceneGenerator::createClouds() {
    auto cloud = std::make_shared<Cloud>(tileFactory, grid, 1);
    cloud->snapToGrid(sf::Vector2i(6, 3));
    ObjectRegistry::add(cloud);
}

void SceneGenerator::createHills() {
    auto hill = std::make_shared<Hill>(tileFactory, grid, 1);
    hill->snapToGrid(sf::Vector2i(7, 8));
    ObjectRegistry::add(hill);
}