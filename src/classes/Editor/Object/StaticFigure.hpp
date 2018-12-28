#pragma once

#include "classes/Editor/Object/AbstractFigure.hpp"

class StaticFigure : AbstractFigure {

public:

    explicit StaticFigure(std::unique_ptr<TileFactory> &tileFactory);

};
