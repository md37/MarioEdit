#include "TileRegistry.hpp"

void TileEventRegistry::registerOver(std::shared_ptr<Tile> tile) {
    if (!isOverRegistered(tile)) {
        registeredOverOnTiles.push_back(tile);
    }
}

void TileEventRegistry::unregisterOver(std::shared_ptr<Tile> tile) {
    if (isOverRegistered(tile)) {
        registeredOverOnTiles.erase(
                std::remove(registeredOverOnTiles.begin(), registeredOverOnTiles.end(), tile), registeredOverOnTiles.end()
        );
    }
}

bool TileEventRegistry::isOverRegistered(std::shared_ptr<Tile> tile) {
    if (registeredOverOnTiles.empty()) {
        return false;
    }

    return std::find(registeredOverOnTiles.begin(), registeredOverOnTiles.end(), tile) != registeredOverOnTiles.end();
}

void TileEventRegistry::registerDrag(std::shared_ptr<DynamicTile> tile) {
    if (!isDragRegistered(tile)) {
        registeredDragOnTiles.push_back(tile);
    }
}

void TileEventRegistry::unregisterDrag(std::shared_ptr<DynamicTile> tile) {
    if (isDragRegistered(tile)) {
        registeredDragOnTiles.erase(
                std::remove(registeredDragOnTiles.begin(), registeredDragOnTiles.end(), tile), registeredDragOnTiles.end()
        );
    }
}

bool TileEventRegistry::isDragRegistered(std::shared_ptr<DynamicTile> tile) {
    if (registeredDragOnTiles.empty()) {
        return false;
    }

    return std::find(this->registeredDragOnTiles.begin(), this->registeredDragOnTiles.end(), tile) != this->registeredDragOnTiles.end();
}

std::vector<std::shared_ptr<DynamicTile>> TileEventRegistry::getRegisteredDragOnTiles() {
    return registeredDragOnTiles;
}
