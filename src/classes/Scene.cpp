#include "Scene.hpp"

#include "defines.hpp"
#include "classes/Scene/Scale.hpp"
#include "classes/Scene/Tile/TileRegistry.hpp"

Scene::Scene(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;

    tileBar = std::make_shared<TileBar>();
    grid = std::make_shared<Grid>(window->getSize());
    scale = std::make_shared<Scale>();
    tileFactory = std::make_shared<TileFactory>("resources/tiles.png", scale);
    tileFactory->setTileSeparators(1, 1);

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
    reScaleTiles();
    reSnapTilesToGrid();
}

void Scene::reSnapTilesToGrid() {
    auto staticTiles = TileRegistry::getStaticTiles();
    for (auto const &tile : staticTiles) {
        tile->snapToGrid();
    }

    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->snapToGrid();
    }
}

void Scene::draw() {
    window->clear(BG_LIGHT_COLOR);

    auto staticTiles = TileRegistry::getStaticTiles();
    for (auto const &tile : staticTiles) {
        tile->draw(window);
    }

    grid->draw(window);
    tileBar->draw(window);

    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->draw(window);
    }
}

void Scene::reScaleTiles() {
    auto staticTiles = TileRegistry::getStaticTiles();
    for (auto const &tile : staticTiles) {
        tile->rescale(scale->getScale());
    }

    auto dynamicTiles = TileRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->rescale(scale->getScale());
    }
}
