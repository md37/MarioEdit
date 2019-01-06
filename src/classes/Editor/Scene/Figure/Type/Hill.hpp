#pragma once

#include "classes/Editor/Object/FigureGenerator/HillGenerator.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"

class Hill : public DynamicFigure {

public:

    Hill(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size);
    Hill(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size);

private:

    HillGenerator generatorObject;

};
