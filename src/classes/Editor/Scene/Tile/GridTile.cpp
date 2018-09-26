#include "GridTile.hpp"

GridTile::GridTile(sf::Sprite sprite, TileConfig config) : Tile(sprite, config) {

}

void GridTile::setGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}

void GridTile::snapToGrid() {
    setPosition(grid->pointOnGridToPosition(gridPosition));
}

void GridTile::snapToGrid(sf::Vector2u gridPosition) {
    this->gridPosition = gridPosition;
    setPosition(grid->pointOnGridToPosition(gridPosition));
}

bool GridTile::isOnIncompletePlace(sf::Vector2u dropPlace) {
    return grid->hasIncompleteEnding() && dropPlace.x == grid->getCols();
}
