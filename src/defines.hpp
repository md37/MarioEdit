#pragma once

#define BIT(x) (1 << x)

#include <variant>
#include "classes/Editor/Navigation/TileButton.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Navigation/FigureButton.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"

typedef std::variant<
    std::shared_ptr<DynamicTile>,
    std::shared_ptr<TileButton>,
    std::shared_ptr<DynamicFigure>,
    std::shared_ptr<FigureButton>
> HoverableItem;

typedef std::variant<
    std::shared_ptr<DynamicTile>,
    std::shared_ptr<DynamicFigure>
> DraggableItem;
