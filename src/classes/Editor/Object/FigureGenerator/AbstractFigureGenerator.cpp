#include "AbstractFigureGenerator.hpp"

AbstractFigureGenerator::AbstractFigureGenerator(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size
): tileFactory(tileFactory) {
    this->grid = grid;
    this->size = size;
}

void AbstractFigureGenerator::updateGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}
