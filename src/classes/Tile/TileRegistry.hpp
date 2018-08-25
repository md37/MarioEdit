#pragma once

#include <vector>
#include "classes/Tile/DynamicTile.hpp"

class TileRegistry {

public:

    static void clear();
    static void registerTile(std::shared_ptr<DynamicTile> tile);
    static std::vector<std::shared_ptr<DynamicTile>> getDynamicTiles();

private:

    static std::vector<std::shared_ptr<DynamicTile>> dynamicTiles;

};
