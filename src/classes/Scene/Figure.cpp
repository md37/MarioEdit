#include "Figure.hpp"

Figure::Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position) {
    this->tileFactory = tileFactory;
    this->grid = grid;
    this->position = position;
}
