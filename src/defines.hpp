#pragma once

#define BIT(x) (1 << x)

#include <variant>
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"

typedef std::variant<
    std::shared_ptr<DynamicTile>,
    std::shared_ptr<ButtonTile>,
    std::shared_ptr<DynamicFigure>
> HoverableItem;

typedef std::variant<
    std::shared_ptr<DynamicTile>,
    std::shared_ptr<DynamicFigure>
> DraggableItem;
