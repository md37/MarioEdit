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

void GridTile::snapToCenterPoint() {
    auto newSpriteScale = scale*scalePromotion;
    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    sprite.setScale(newSpriteScale.x, newSpriteScale.y);

    position.x = centerPoint.x-newWidth/2;
    position.y = centerPoint.y-newHeight/2;
    sprite.setPosition(position);
}

bool GridTile::isOnIncompletePlace() {
    return grid->isHighlightOnIncompletePlace();
}
