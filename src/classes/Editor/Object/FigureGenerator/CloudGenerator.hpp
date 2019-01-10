#pragma once

#include "classes/Editor/Object/FigureGenerator/AbstractFigureGenerator.hpp"

class CloudGenerator : public AbstractFigureGenerator {

public:

    CloudGenerator(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid);

    std::vector<std::shared_ptr<StaticTile>> generate(sf::Vector2i pointOnGrid, sf::Uint8 size) override;

};
