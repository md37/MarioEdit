#include "SceneGenerator.hpp"

#include "classes/Editor/Scene/Figure/Type/Bush.hpp"
#include "classes/Editor/Scene/Figure/Type/Cloud.hpp"
#include "classes/Editor/Scene/Figure/Type/Hill.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

SceneGenerator::SceneGenerator(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid>& grid): tileFactory(tileFactory), grid(grid) {

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
    auto bush = std::make_shared<Bush>(tileFactory, 1);
    bush->snapToGrid(sf::Vector2i(2, 9));
    ObjectRegistry::add(bush);
}

void SceneGenerator::createClouds() {
    auto cloud = std::make_shared<Cloud>(tileFactory, 1);
    cloud->snapToGrid(sf::Vector2i(4, 6));
    ObjectRegistry::add(cloud);
}

void SceneGenerator::createHills() {
    auto hill = std::make_shared<Hill>(tileFactory, 1);
    hill->snapToGrid(sf::Vector2i(7, 8));
    ObjectRegistry::add(hill);
}