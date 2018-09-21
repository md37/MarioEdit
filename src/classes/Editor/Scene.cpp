#include "Scene.hpp"

#include "classes/System/Scale.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

Scene::Scene(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Scale> scale) {
    this->scale = scale;

    grid = std::make_shared<Grid>();
    sceneGenerator = std::make_shared<SceneGenerator>(tileFactory, grid);
    sceneGenerator->generate();

    blinkAnimation = std::make_shared<SpecialBlockBlinkAnimation>();
}

void Scene::startTasks() {
    blinkAnimation->run();
}

void Scene::rescale(sf::Vector2u windowSize) {
    grid->rescale(windowSize);
    reScaleTiles();
    reSnapTilesToGrid();
}

void Scene::reScaleTiles() {
    auto allTiles = ObjectRegistry::getAllTiles();
    for (auto const &tile : allTiles) {
        tile->rescale(scale->getScale());
    }
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
        tile->draw(window);
    }
}