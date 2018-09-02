#include "Scene.hpp"

#include "defines.hpp"
#include "classes/Scene/Scale.hpp"
#include "classes/Scene/SceneRegistry.hpp"

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
    auto figures = SceneRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->snapToGrid();
    }

    auto dynamicTiles = SceneRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->snapToGrid();
    }
}

void Scene::draw() {
    window->clear(BG_LIGHT_COLOR);

    auto figures = SceneRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->draw(window);
    }

    grid->draw(window);
    tileBar->draw(window);

    auto dynamicTiles = SceneRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        if (tile->isMouseOver() || tile->isDragging()) {
            continue;
        }
        tile->draw(window);
    }

    auto highlightedTile = SceneRegistry::getHighlightedTile();
    if (highlightedTile != nullptr) {
        highlightedTile->draw(window);
    }
}

void Scene::reScaleTiles() {
    auto allTiles = SceneRegistry::getAllTiles();
    for (auto const &tile : allTiles) {
        tile->rescale(scale->getScale());
    }
}
