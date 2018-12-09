#include "GridTile.hpp"

GridTile::GridTile(sf::Sprite sprite, std::unique_ptr<Grid>& grid, TileConfig config) : Tile(sprite, config), grid(grid) {

}

void GridTile::snapToGrid() {
    setPosition(grid->pointOnGridToPosition(pointOnGrid));
}

void GridTile::snapToGrid(sf::Vector2i pointOnGrid) {
    this->pointOnGrid = pointOnGrid;
    setPosition(grid->pointOnGridToPosition(pointOnGrid));
}

bool GridTile::isOnIncompletePoint(sf::Vector2i pointOnGrid) {
    return grid->hasIncompleteEnding() && pointOnGrid.x == grid->getCols();
}

sf::Vector2i GridTile::getPointOnGrid() {
    return pointOnGrid;
}

sf::Vector2u GridTile::getSizeOnGrid() {
    return {1, 1};
}
