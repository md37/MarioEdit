#include "Hill.hpp"

Hill::Hill(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Vector2u size) : Figure(tileFactory, grid, position) {
    this->size = size;
}

void Hill::createTiles() {

}
