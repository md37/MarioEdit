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

void GridTile::snapToWindowBound() {
    if (isOnTopLeftCorner()) {
        snapToTopLeftCorner();
    } else if (isOnBottomLeftCorner()) {
        snapToBottomLeftCorner();
    } else if (isOnBottomRightCorner()) {
        snapToBottomRightCorner();
    } else if (isOnTopRightCorner()) {
        snapToTopRightCorner();
    } else if (isOnLeftEdge()) {
        snapToLeftEdge();
    } else if (isOnRightEdge()) {
        snapToRightEdge();
    } else if (isOnTopEdge()) {
        snapToTopEdge();
    } else if (isOnBottomEdge()) {
        snapToBottomEdge();
    } else {
        snapToCenterPoint();
    }
}

bool GridTile::isOnLeftEdge() {
    return gridPosition.x == 0;
}

bool GridTile::isOnRightEdge() {
    if (grid->hasIncompleteEnding()) {
        return false;
    }
    return gridPosition.x == grid->getSize().x-1;
}

bool GridTile::isOnTopEdge() {
    return gridPosition.y == grid->getSize().y-1;
}

bool GridTile::isOnBottomEdge() {
    return gridPosition.y == 0;
}

bool GridTile::isOnTopRightCorner() {
    return isOnTopEdge() && isOnRightEdge();
}

bool GridTile::isOnBottomRightCorner() {
    return isOnBottomEdge() && isOnRightEdge();
}

bool GridTile::isOnBottomLeftCorner() {
    return isOnBottomEdge() && isOnLeftEdge();
}

bool GridTile::isOnTopLeftCorner() {
    return isOnTopEdge() && isOnLeftEdge();
}

void GridTile::snapToTopLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = 0;
    sprite.setPosition(position);
}

void GridTile::snapToBottomLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void GridTile::snapToBottomRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void GridTile::snapToTopRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = 0;
    sprite.setPosition(position);
}

void GridTile::snapToLeftEdge() {
    snapToCenterPoint();
    position.x = 0;
    sprite.setPosition(position);
}

void GridTile::snapToRightEdge() {
    snapToCenterPoint();
    position.x = window->getSize().x-getSize().x;
    sprite.setPosition(position);
}

void GridTile::snapToTopEdge() {
    snapToCenterPoint();
    position.y = 0;
    sprite.setPosition(position);
}

void GridTile::snapToBottomEdge() {
    snapToCenterPoint();
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void GridTile::snapToCenterPoint() {
    auto center = grid->getCenter(gridPosition);

    auto newSpriteScale = scale*scalePromotion;
    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    sprite.setScale(newSpriteScale.x, newSpriteScale.y);

    position.x = center.x-newWidth/2;
    position.y = center.y-newHeight/2;
    sprite.setPosition(position);
}
