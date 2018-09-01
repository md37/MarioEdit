#pragma once

#include <vector>
#include "classes/Scene/Figure.hpp"
#include "classes/Scene/Tile/DynamicTile.hpp"

class SceneRegistry {

public:

    static void clear();
    static void registerTile(std::shared_ptr<Tile> tile);
    static void registerTile(std::shared_ptr<DynamicTile> tile);
    static void registerFigure(std::shared_ptr<Figure> figure);
    static std::vector<std::shared_ptr<Tile>> getAllTiles();
    static std::vector<std::shared_ptr<DynamicTile>> getDynamicTiles();
    static std::vector<std::shared_ptr<Figure>> getFigures();

private:

    static std::vector<std::shared_ptr<Tile>> allTiles;
    static std::vector<std::shared_ptr<DynamicTile>> dynamicTiles;
    static std::vector<std::shared_ptr<Figure>> figures;

};
