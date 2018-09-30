#pragma once

#include <vector>
#include "classes/System/Interface/DraggableInterface.hpp"
#include "classes/System/Interface/HoverableInterface.hpp"
#include "classes/Editor/Scene/Figure.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"

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

    static std::vector<std::shared_ptr<DynamicTile>> getHighlightedTiles();
    static std::vector<std::shared_ptr<DynamicTile>> getReturningTiles();
    static std::vector<std::shared_ptr<Figure>> getFigures();

    static std::shared_ptr<DynamicTile> getTileOnGrid(sf::Vector2u gridPlace);

    static void removeTile(std::shared_ptr<DynamicTile> tile);

private:

    static std::vector<std::shared_ptr<Tile>> allTiles;
    static std::vector<std::shared_ptr<DynamicTile>> dynamicTiles;
    static std::vector<std::shared_ptr<ButtonTile>> buttonTiles;
    static std::vector<std::shared_ptr<Figure>> figures;

};