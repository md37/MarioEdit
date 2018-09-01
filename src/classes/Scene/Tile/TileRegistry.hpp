#pragma once

#include <vector>
#include "classes/Scene/Tile/DynamicTile.hpp"
#include "classes/Scene/Tile/StaticTile.hpp"

class TileRegistry {

public:

    static void clear();
    static void registerTile(std::shared_ptr<DynamicTile> tile);
    static void registerTile(std::shared_ptr<StaticTile> tile);
    static std::vector<std::shared_ptr<DynamicTile>> getDynamicTiles();
    static std::vector<std::shared_ptr<StaticTile>> getStaticTiles();

private:

    static std::vector<std::shared_ptr<DynamicTile>> dynamicTiles;
    static std::vector<std::shared_ptr<StaticTile>> staticTiles;

};
