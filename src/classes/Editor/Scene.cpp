#include "Scene.hpp"

#include "classes/Infrastructure/Scale.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

Scene::Scene(std::unique_ptr<TileFactory> &tileFactory) {
    Settings gridSettings(
        12, Settings::Auto, sf::Vector2f(0, 0), sf::Vector2f(Settings::Auto, Settings::Auto)
    );
    grid = std::make_shared<Grid>(gridSettings);

    sceneGenerator = std::make_unique<SceneGenerator>(tileFactory, grid);
    sceneGenerator->generate();
}

void Scene::rescale(std::unique_ptr<Scale> &scale) {
    grid->rescale(scale);
    reScaleTiles(scale);
    reSnapTilesToGrid();
}

void Scene::reScaleTiles(std::unique_ptr<Scale> &scale) {
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

void Scene::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->clear(sf::Color(92, 148, 252));

    auto figures = ObjectRegistry::getFigures();

    for (auto const &figure : figures) {
        if (figure->isDragging()) {
            continue;
        }
        figure->draw(window);
    }

    for (auto const &figure : figures) {
        if (figure->isDragging()) {
            figure->draw(window);
        }
    }

    grid->draw(window);

    for (auto const &figure : figures) {
        if (figure->isMouseOver()) {
            figure->drawFrame(window);
        }
    }

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

std::shared_ptr<DynamicTile> Scene::getDraggingTile() const {
    auto dynamicTiles = ObjectRegistry::getDynamicTiles();
    for (auto const &tile : dynamicTiles) {
        if (tile->isDragging()) {
            return tile;
        }
    }
    return nullptr;
}
