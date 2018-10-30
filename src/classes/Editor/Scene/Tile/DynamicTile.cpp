#include <classes/Editor/ObjectRegistry.hpp>
#include "DynamicTile.hpp"

#include "classes/System/Cursor.hpp"

DynamicTile::DynamicTile(sf::Sprite sprite, TileConfig config) : GridTile(sprite, config) {

}

void DynamicTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

bool DynamicTile::isMouseOver() {
    return isMouseOverFlag;
}

void DynamicTile::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
    if (undoHighlightAnimation.use_count()) {
        undoHighlightAnimation->stop();
    }

    highlightAnimation = std::make_shared<HighlightAnimation>(this);
    animationPerformer->add(highlightAnimation);
}

void DynamicTile::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void DynamicTile::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
    isReturning = true;
    if (highlightAnimation.use_count()) {
        highlightAnimation->stop();
    }

    undoHighlightAnimation = std::make_shared<UndoHighlightAnimation>(this);
    animationPerformer->add(undoHighlightAnimation);
}

bool DynamicTile::isDragging() {
    return isDraggingFlag;
}

void DynamicTile::startDrag(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->turnHighlightOn(getSizeOnGrid());
    isDraggingFlag = true;
}

void DynamicTile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void DynamicTile::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    dragOffset = {0, 0};

    dropHighlightPlace = grid->getHighlightPointOnGrid();
    snapToGrid(dropHighlightPlace);

    sf::Vector2f positionOnGrid = grid->getHighlightPosition();
    sf::Vector2f tileSize(getSize());
    positionOnGrid -= (tileSize-(tileSize/scalePromotion))/2.0f;

    setPosition(positionOnGrid);

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

    sprite.setPosition(sf::Vector2f(posX, posY));
}

sf::Vector2i DynamicTile::getDropHighlightPlace() {
    return dropHighlightPlace;
}
