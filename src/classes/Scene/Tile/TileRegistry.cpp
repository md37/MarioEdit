#include "TileRegistry.hpp"

std::vector<std::shared_ptr<DynamicTile>> TileRegistry::dynamicTiles;
std::vector<std::shared_ptr<StaticTile>> TileRegistry::staticTiles;

void TileRegistry::clear() {
    dynamicTiles.clear();
}

void TileRegistry::registerTile(std::shared_ptr<DynamicTile> tile) {
    dynamicTiles.push_back(tile);
}

void TileRegistry::registerTile(std::shared_ptr<StaticTile> tile) {
    staticTiles.push_back(tile);
}

std::vector<std::shared_ptr<DynamicTile>> TileRegistry::getDynamicTiles() {
    return dynamicTiles;
}

std::vector<std::shared_ptr<StaticTile>> TileRegistry::getStaticTiles() {
    return staticTiles;
}
