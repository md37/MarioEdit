#include "AbstractFigureGenerator.hpp"

AbstractFigureGenerator::AbstractFigureGenerator(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid
): tileFactory(tileFactory) {
    this->grid = grid;
}

void AbstractFigureGenerator::updateGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}
