#pragma once

#include "classes/Editor/Object/AbstractFigure.hpp"

class StaticFigure : public AbstractFigure {

public:

    explicit StaticFigure(std::unique_ptr<TileFactory> &tileFactory);

};
