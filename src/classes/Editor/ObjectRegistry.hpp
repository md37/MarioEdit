#pragma once

#include <vector>
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Editor/Navigation/FigureButton.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Navigation/TileButton.hpp"

class DynamicFigure;

class ObjectRegistry {

public:

    static void clear();
    static void add(std::shared_ptr<AbstractTile> tile);
    static void add(std::shared_ptr<DynamicTile> tile);
    static void add(std::shared_ptr<TileButton> tile);
    static void add(std::shared_ptr<DynamicFigure> figure);
    static void add(std::shared_ptr<FigureButton> figure);

    static std::vector<std::shared_ptr<AbstractTile>> getAllTiles();

    static std::vector<std::shared_ptr<DynamicTile>> getDynamicTiles();
    static std::vector<std::shared_ptr<TileButton>> getButtonTiles();

    static std::vector<std::shared_ptr<DynamicTile>> getHighlightedTiles();
    static std::vector<std::shared_ptr<DynamicTile>> getReturningTiles();

    static std::vector<std::shared_ptr<DynamicFigure>> getFigures();
    static std::vector<std::shared_ptr<FigureButton>> getButtonFigures();

    static std::shared_ptr<DynamicTile> getTileOnGrid(sf::Vector2i gridPoint);

    static void removeTile(std::shared_ptr<DynamicTile> tile);
    static void removeFigure(std::shared_ptr<DynamicFigure> figure);

private:

    static std::vector<std::shared_ptr<AbstractTile>> allTiles;
    static std::vector<std::shared_ptr<DynamicTile>> dynamicTiles;
    static std::vector<std::shared_ptr<TileButton>> buttonTiles;
    static std::vector<std::shared_ptr<DynamicFigure>> figures;
    static std::vector<std::shared_ptr<FigureButton>> buttonFigures;

};
