#pragma once

#include "classes/Editor/Object/FigureGenerator/CloudGenerator.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"

class Cloud : public DynamicFigure {

public:

    Cloud(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size);
    Cloud(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size);

private:

    CloudGenerator generatorObject;
};
