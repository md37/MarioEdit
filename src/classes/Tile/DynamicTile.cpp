#include "DynamicTile.hpp"

#include "classes/Cursor.hpp"

DynamicTile::DynamicTile(sf::Sprite sprite, TileConfig config) : Tile(sprite, config) {
    highlightTileAnimation = std::make_shared<HighlightTileAnimation>(this);
    undoHighlightTileAnimation = std::make_shared<UndoHighlightTileAnimation>(this);
}

void DynamicTile::handleEvent(DynamicTile::Event event) {
    if (eventCallbacks.find(event) == eventCallbacks.end()) {
        return;
    }
    eventCallbacks[event](this);
}

void DynamicTile::setEventHandler(DynamicTile::Event event, std::function<void(DynamicTile* tile)> callback) {
    eventCallbacks[event] = callback;
}

void DynamicTile::startDrag() {
    sprite.setColor(sf::Color(255, 255, 255, 180));

    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->turnHighlightOn();
}

void DynamicTile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void DynamicTile::drop() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
    dragOffset = {0, 0};

    snapToGrid(grid->getHighlightPlace());

    sf::Vector2f positionOnGrid = grid->getHighlightPosition();
    sf::Vector2f tileSize(getSize());
    positionOnGrid -= (tileSize-(tileSize/scalePromotion))/2.0f;

    setPosition(positionOnGrid);
    grid->turnHighlightOff();

    correctCorners();
}

bool DynamicTile::isMouseOver() {
    return isMouseOverFlag;
}

bool DynamicTile::isDragging() {
    return isDraggingFlag;
}

void DynamicTile::highlight() {
    if (undoHighlightTileAnimation->isRunning()) {
        undoHighlightTileAnimation->stop();
    }
    if (!highlightTileAnimation->isRunning()) {
        highlightTileAnimation->run();
    }
}

void DynamicTile::undoHighlight() {
    if (highlightTileAnimation->isRunning()) {
        highlightTileAnimation->stop();
    }
    if (!undoHighlightTileAnimation->isRunning()) {
        undoHighlightTileAnimation->run();
    }
}

void DynamicTile::snapToCenterPoint() {
    auto center = grid->getCenter(gridPosition);

    auto newSpriteScale = scale*scalePromotion;
    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    sprite.setScale(newSpriteScale.x, newSpriteScale.y);

    position.x = center.x-newWidth/2;
    position.y = center.y-newHeight/2;
    sprite.setPosition(position);
}

void DynamicTile::snapToWindowBound() {
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

bool DynamicTile::isOnLeftEdge() {
    return gridPosition.x == 0;
}

bool DynamicTile::isOnRightEdge() {
    if (grid->hasIncompleteEnding()) {
        return false;
    }
    return gridPosition.x == grid->getSize().x-1;
}

bool DynamicTile::isOnTopEdge() {
    return gridPosition.y == grid->getSize().y-1;
}

bool DynamicTile::isOnBottomEdge() {
    return gridPosition.y == 0;
}

bool DynamicTile::isOnTopRightCorner() {
    return isOnTopEdge() && isOnRightEdge();
}

bool DynamicTile::isOnBottomRightCorner() {
    return isOnBottomEdge() && isOnRightEdge();
}

bool DynamicTile::isOnBottomLeftCorner() {
    return isOnBottomEdge() && isOnLeftEdge();
}

bool DynamicTile::isOnTopLeftCorner() {
    return isOnTopEdge() && isOnLeftEdge();
}

void DynamicTile::snapToTopLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = 0;
    sprite.setPosition(position);
}

void DynamicTile::snapToBottomLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void DynamicTile::snapToBottomRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void DynamicTile::snapToTopRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = 0;
    sprite.setPosition(position);
}

void DynamicTile::snapToLeftEdge() {
    snapToCenterPoint();
    position.x = 0;
    sprite.setPosition(position);
}

void DynamicTile::snapToRightEdge() {
    snapToCenterPoint();
    position.x = window->getSize().x-getSize().x;
    sprite.setPosition(position);
}

void DynamicTile::snapToTopEdge() {
    snapToCenterPoint();
    position.y = 0;
    sprite.setPosition(position);
}

void DynamicTile::snapToBottomEdge() {
    snapToCenterPoint();
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void DynamicTile::correctCorners() {
    auto width = getSize().x;
    auto height = getSize().y;

    auto posX = sprite.getPosition().x;
    if (posX < 0) {
        posX = 0;
    }

    auto posY = sprite.getPosition().y;
    if (posY < 0) {
        posY = 0;
    }

    auto windowWidth = Tile::window->getSize().x;
    if (posX+width > windowWidth) {
        posX = windowWidth-width;
    }

    auto windowHeight = Tile::window->getSize().y;
    if (posY+height > windowHeight) {
        posY = windowHeight-height;
    }

    position = sf::Vector2f(posX, posY);
    sprite.setPosition(position);
}