#include "Cloud.hpp"

Cloud::Cloud(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size) : Figure (tileFactory, grid, position) {
    this->size = size;
}

void Cloud::createTiles() {

}
