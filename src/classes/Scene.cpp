#include "Scene.hpp"

#include "defines.hpp"
#include "classes/Scene/Scale.hpp"
#include "classes/Scene/Tile/TileRegistry.hpp"

Scene::Scene(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;
    tileBar = std::make_shared<TileBar>();
    grid = std::make_shared<Grid>(window->getSize());
    scale = std::make_shared<Scale>();
    tileFactory = std::make_shared<TileFactory>("resources/tiles2.png", scale);

    sceneGenerator = std::make_shared<SceneGenerator>(tileFactory, grid);
    sceneGenerator->generate();

    blinkAnimation = std::make_shared<SpecialBlockBlinkingAnimation>();
}

std::shared_ptr<Scale> Scene::getScale() {
    return scale;
}

void Scene::runTasks() {
    blinkAnimation->run();
}

void Scene::rescale() {
    scale->rescale(window->getSize());
    Tile::setWindow(window);
    grid->rescale(window->getSize());
    reSnapTilesToGrid();
}

void Scene::reSnapTilesToGrid() {
    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (size_t i=0; i < dynamicTiles.size(); i++) {
        auto tile = dynamicTiles[i];
        tile->snapToGrid();
    }
}

void Scene::draw() {
    window->clear(BG_LIGHT_COLOR);
    grid->draw(window);
    tileBar->draw(window);

    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (std::size_t i=0; i<dynamicTiles.size(); i++) {
        dynamicTiles[i]->draw(window);
    }
}
