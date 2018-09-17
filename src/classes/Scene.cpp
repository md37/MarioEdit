#include "Scene.hpp"

#include "defines.hpp"
#include "classes/Scene/Scale.hpp"
#include "classes/ObjectRegistry.hpp"

Scene::Scene(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;

    grid = std::make_shared<Grid>();
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

void Scene::rescale(sf::Vector2u windowSize) {
    scale->rescale(windowSize);
    grid->rescale(windowSize);
    Tile::setWindow(window);
    reScaleTiles();
    reSnapTilesToGrid();
}

void Scene::reSnapTilesToGrid() {
    auto figures = ObjectRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->snapToGrid();
    }

    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->snapToGrid();
    }
}

void Scene::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->clear(BG_LIGHT_COLOR);

    auto figures = ObjectRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->draw(window);
    }

    grid->draw(window);

    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        if (tile->isMouseOver() || tile->isDragging()) {
            continue;
        }
        tile->draw(window);
    }

    auto highlightedTile = ObjectRegistry::getHighlightedTile();
    if (highlightedTile != nullptr) {
        highlightedTile->draw(window);
    }
}

void Scene::reScaleTiles() {
    auto allTiles = ObjectRegistry::getAllTiles();
    for (auto const &tile : allTiles) {
        tile->rescale(scale->getScale());
    }
}
