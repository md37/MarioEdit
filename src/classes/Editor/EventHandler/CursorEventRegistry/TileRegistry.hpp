#pragma once

#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

class TileEventRegistry {

public:

    void registerOver(std::shared_ptr<Tile> tile);
    void unregisterOver(std::shared_ptr<Tile> tile);
    bool isOverRegistered(std::shared_ptr<Tile> tile);

    void registerDrag(std::shared_ptr<DynamicTile> tile);
    void unregisterDrag(std::shared_ptr<DynamicTile> tile);
    bool isDragRegistered(std::shared_ptr<DynamicTile> tile);

    std::vector<std::shared_ptr<DynamicTile>> getRegisteredDragOnTiles();

private:

    std::vector<std::shared_ptr<Tile>> registeredOverOnTiles;
    std::vector<std::shared_ptr<DynamicTile>> registeredDragOnTiles;

};
