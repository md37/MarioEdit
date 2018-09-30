#include "Scene.hpp"

#include "classes/System/Scale.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

Scene::Scene(std::shared_ptr<TileFactory> tileFactory) {
    grid = std::make_shared<Grid>();
    sceneGenerator = std::make_shared<SceneGenerator>(tileFactory, grid);
    sceneGenerator->generate();

    blinkAnimation = std::make_shared<SpecialBlockBlinkAnimation>();
}

void Scene::startTasks() {
    blinkAnimation->run();
}

void Scene::rescale(std::shared_ptr<Scale> scale) {
    grid->rescale(scale);
    reScaleTiles(scale);
    reSnapTilesToGrid();
}

void Scene::reScaleTiles(std::shared_ptr<Scale> scale) {
    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->rescale(scale);
    }

    auto figures = ObjectRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->rescale(scale);
    }
}

void Scene::reSnapTilesToGrid() {
    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        tile->snapToGrid();
    }

    auto figures = ObjectRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->snapToGrid();
    }
}

void Scene::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->clear(sf::Color(92, 148, 252));

    auto figures = ObjectRegistry::getFigures();
    for (auto const &figure : figures) {
        figure->draw(window);
    }

    grid->draw(window);

    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        if (tile->isMouseOver() || tile->isDragging() || tile->isReturning) {
            continue;
        }
        tile->draw(window);
    }

    auto returningTiles = ObjectRegistry::getReturningTiles();
    for (auto const &tile : returningTiles) {
        tile->draw(window);
    }

    auto highlightedTiles = ObjectRegistry::getHighlightedTiles();
    for (auto const &tile : highlightedTiles) {
        if (tile->isDragging()) {
            continue;
        }
        tile->draw(window);
    }
}

std::shared_ptr<Grid> Scene::getGrid() {
    return grid;
}

std::shared_ptr<DynamicTile> Scene::getDraggingTile() {
    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        if (tile->isDragging()) {
            return tile;
        }
    }
    return nullptr;
}
