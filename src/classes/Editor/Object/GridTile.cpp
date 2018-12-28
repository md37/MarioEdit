#include "GridTile.hpp"

GridTile::GridTile(sf::Sprite sprite, std::shared_ptr<Grid>& grid, TileConfig config) : AbstractTile(sprite, config), grid(grid) {

}

void GridTile::snapToGrid() {
    setPosition(grid->pointOnGridToPosition(pointOnGrid));
}

void GridTile::snapToGrid(sf::Vector2i pointOnGrid) {
    this->pointOnGrid = pointOnGrid;
    setPosition(grid->pointOnGridToPosition(pointOnGrid));
}

bool GridTile::isOnIncompletePoint(sf::Vector2i pointOnGrid) const {
    return grid->hasIncompleteEnding() && pointOnGrid.x == grid->getCols();
}

sf::Vector2i GridTile::getPointOnGrid() const {
    return pointOnGrid;
}

sf::Vector2u GridTile::getSizeOnGrid() const {
    return {1, 1};
}
