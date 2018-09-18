#pragma once

#include <vector>
#include "classes/Interface/HoverableInterface.hpp"
#include "classes/Interface/DraggableInterface.hpp"
#include "classes/Editor/Scene/Figure.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Tilebar/Tile/ButtonTile.hpp"

class ObjectRegistry {

public:

    static void clear();
    static void registerTile(std::shared_ptr<Tile> tile);
    static void registerTile(std::shared_ptr<DynamicTile> tile);
    static void registerTile(std::shared_ptr<ButtonTile> tile);
    static void registerFigure(std::shared_ptr<Figure> figure);

    static std::vector<std::shared_ptr<Tile>> getAllTiles();

    static std::vector<std::shared_ptr<DynamicTile>> getDynamicTiles();
    static std::vector<std::shared_ptr<ButtonTile>> getButtonTiles();

    static std::shared_ptr<DynamicTile> getHighlightedTile();
    static std::vector<std::shared_ptr<Figure>> getFigures();

private:

    static std::vector<std::shared_ptr<Tile>> allTiles;
    static std::vector<std::shared_ptr<DynamicTile>> dynamicTiles;
    static std::vector<std::shared_ptr<ButtonTile>> buttonTiles;
    static std::vector<std::shared_ptr<Figure>> figures;

};
