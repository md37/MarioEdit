#include "Figure.hpp"

Figure::Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position) {
    this->tileFactory = tileFactory;
    this->grid = grid;
    this->position = position;
}

void Figure::snapToGrid() {
    for (auto tile : tiles) {
        tile->snapToGrid();
    }
}

void Figure::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (auto tile : tiles) {
        tile->draw(window);
    }
}
