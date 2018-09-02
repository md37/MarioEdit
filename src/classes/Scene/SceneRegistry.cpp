#include "SceneRegistry.hpp"

std::vector<std::shared_ptr<Tile>> SceneRegistry::allTiles;
std::vector<std::shared_ptr<DynamicTile>> SceneRegistry::dynamicTiles;
std::vector<std::shared_ptr<Figure>> SceneRegistry::figures;

void SceneRegistry::clear() {
    dynamicTiles.clear();
}

void SceneRegistry::registerTile(std::shared_ptr<Tile> tile) {
    allTiles.push_back(tile);
}

void SceneRegistry::registerTile(std::shared_ptr<DynamicTile> tile) {
    allTiles.push_back(tile);
    dynamicTiles.push_back(tile);
}

void SceneRegistry::registerFigure(std::shared_ptr<Figure> figure) {
    figures.push_back(figure);
}

std::vector<std::shared_ptr<Tile>> SceneRegistry::getAllTiles() {
    return allTiles;
}

std::shared_ptr<DynamicTile> SceneRegistry::getHighlightedTile() {
    for (auto tile : dynamicTiles) {
        if (tile->isMouseOver() || tile->isDragging()) {
            return tile;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<DynamicTile>> SceneRegistry::getDynamicTiles() {
    return dynamicTiles;
}

std::vector<std::shared_ptr<Figure>> SceneRegistry::getFigures() {
    return figures;
}
