#include "DynamicTile.hpp"

#include "classes/System/Cursor.hpp"

DynamicTile::DynamicTile(sf::Sprite sprite, TileConfig config) : GridTile(sprite, config) {
    highlightAnimation = std::make_shared<HighlightAnimation>(this);
    undoHighlightAnimation = std::make_shared<UndoHighlightAnimation>(this);
}

void DynamicTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

bool DynamicTile::isMouseOver() {
    return isMouseOverFlag;
}

bool DynamicTile::isDragging() {
    return isDraggingFlag;
}

void DynamicTile::mouseEnter() {
    isMouseOverFlag = true;
    if (undoHighlightAnimation->isRunning()) {
        undoHighlightAnimation->stop();
    }
    if (!highlightAnimation->isRunning()) {
        highlightAnimation->run();
    }
}

void DynamicTile::mouseOver() {

}

void DynamicTile::mouseLeave() {
    isMouseOverFlag = false;
    if (highlightAnimation->isRunning()) {
        highlightAnimation->stop();
    }
    if (!undoHighlightAnimation->isRunning()) {
        undoHighlightAnimation->run();
    }
}

void DynamicTile::startDrag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->turnHighlightOn();
    isDraggingFlag = true;
}

void DynamicTile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void DynamicTile::drop() {
    dragOffset = {0, 0};

    snapToGrid(grid->getHighlightPlace());

    sf::Vector2f positionOnGrid = grid->getHighlightPosition();
    sf::Vector2f tileSize(getSize());
    positionOnGrid -= (tileSize-(tileSize/scalePromotion))/2.0f;

    this->position = positionOnGrid;
    sprite.setPosition(positionOnGrid);
    recalculateCenter();

    grid->turnHighlightOff();

    correctCorners();
    isDraggingFlag = false;
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
