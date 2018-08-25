#include "TileRegistry.hpp"

std::vector<std::shared_ptr<DynamicTile>> TileRegistry::dynamicTiles;

void TileRegistry::clear() {
    dynamicTiles.clear();
}

void TileRegistry::registerTile(std::shared_ptr<DynamicTile> tile) {
    dynamicTiles.push_back(tile);
}

std::vector<std::shared_ptr<DynamicTile>> TileRegistry::getDynamicTiles() {
    return dynamicTiles;
}