#include "Figure.hpp"

Figure::Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position) {
    this->tileFactory = tileFactory;
    this->grid = grid;
    this->position = position;
}

void Figure::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (auto tile : tiles) {
        tile->draw(window);
    }
}

void Figure::rescale(std::shared_ptr<Scale> scale) {
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
}

void Figure::snapToGrid() {
    for (auto tile : tiles) {
        tile->snapToGrid();
    }
}
