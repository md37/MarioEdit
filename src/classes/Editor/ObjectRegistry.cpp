#include "ObjectRegistry.hpp"

#include "classes/Editor/Scene/Figure.hpp"

std::vector<std::shared_ptr<Tile>> ObjectRegistry::allTiles;
std::vector<std::shared_ptr<DynamicTile>> ObjectRegistry::dynamicTiles;
std::vector<std::shared_ptr<ButtonTile>> ObjectRegistry::buttonTiles;
std::vector<std::shared_ptr<Figure>> ObjectRegistry::figures;

void ObjectRegistry::clear() {
    dynamicTiles.clear();
}

void ObjectRegistry::add(std::shared_ptr<Tile> tile) {
    allTiles.push_back(tile);
}

void ObjectRegistry::add(std::shared_ptr<DynamicTile> tile) {
    allTiles.push_back(tile);
    dynamicTiles.push_back(tile);
}

void ObjectRegistry::add(std::shared_ptr<ButtonTile> tile) {
    allTiles.push_back(tile);
    buttonTiles.push_back(tile);
}

void ObjectRegistry::add(std::shared_ptr<Figure> figure) {
    figures.push_back(figure);
}

std::vector<std::shared_ptr<Tile>> ObjectRegistry::getAllTiles() {
    return allTiles;
}

std::vector<std::shared_ptr<DynamicTile>> ObjectRegistry::getHighlightedTiles() {
    std::vector<std::shared_ptr<DynamicTile>> tiles;
    for (auto &tile : dynamicTiles) {
        if (tile->isMouseOver() || tile->isDragging()) {
            tiles.push_back(tile);
        }
    }
    return tiles;
}

std::vector<std::shared_ptr<DynamicTile>> ObjectRegistry::getReturningTiles() {
    std::vector<std::shared_ptr<DynamicTile>> tiles;
    for (auto &tile : dynamicTiles) {
        if (tile->isReturning) {
            tiles.push_back(tile);
        }
    }
    return tiles;
}

std::vector<std::shared_ptr<DynamicTile>> ObjectRegistry::getDynamicTiles() {
    return dynamicTiles;
}

std::vector<std::shared_ptr<ButtonTile>> ObjectRegistry::getButtonTiles() {
    return buttonTiles;
}

std::vector<std::shared_ptr<Figure>> ObjectRegistry::getFigures() {
    return figures;
}

std::shared_ptr<DynamicTile> ObjectRegistry::getTileOnGrid(sf::Vector2i gridPoint) {
    for (auto &tile : dynamicTiles) {
        if (tile->getPointOnGrid() == gridPoint) {
            return tile;
        }
    }
    return nullptr;
}

void ObjectRegistry::removeTile(std::shared_ptr<DynamicTile> tile) {
    dynamicTiles.erase(std::remove(dynamicTiles.begin(), dynamicTiles.end(), tile), dynamicTiles.end());
}
