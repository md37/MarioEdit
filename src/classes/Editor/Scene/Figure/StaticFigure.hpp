#pragma once

#include "classes/Editor/Object/Figure.hpp"

class StaticFigure : Figure {

public:

    explicit StaticFigure(std::unique_ptr<TileFactory> &tileFactory);

};
