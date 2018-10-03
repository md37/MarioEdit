#include <classes/Editor/ObjectRegistry.hpp>
#include "DynamicTile.hpp"

#include "classes/System/Cursor.hpp"

DynamicTile::DynamicTile(sf::Sprite sprite, TileConfig config) : GridTile(sprite, config) {
    highlightAnimation = std::make_shared<HighlightAnimation>(this);
    undoHighlightAnimation = std::make_shared<UndoHighlightAnimation>(this);

    undoHighlightAnimation->setFinishCallback([=]() mutable {
        this->isReturning = false;
    });
}

void DynamicTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

bool DynamicTile::isMouseOver() {
    return isMouseOverFlag;
}

void DynamicTile::mouseEnter(AnimationPerformer& animationPerformer) {
    isMouseOverFlag = true;
    undoHighlightAnimation->stop();

    animationPerformer.add(highlightAnimation);
}

void DynamicTile::mouseOver(AnimationPerformer& animationPerformer) {

}

void DynamicTile::mouseLeave(AnimationPerformer& animationPerformer) {
    isMouseOverFlag = false;
    isReturning = true;
    highlightAnimation->stop();

    animationPerformer.add(undoHighlightAnimation);
}

bool DynamicTile::isDragging() {
    return isDraggingFlag;
}

void DynamicTile::startDrag(AnimationPerformer& animationPerformer) {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->turnHighlightOn();
    isDraggingFlag = true;
}

void DynamicTile::drag(AnimationPerformer& animationPerformer) {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHighlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void DynamicTile::drop(AnimationPerformer& animationPerformer) {
    dragOffset = {0, 0};

    dropHighlightPlace = grid->getHighlightPlace();
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

    position = sf::Vector2f(posX, posY);
    sprite.setPosition(position);
}

sf::Vector2u DynamicTile::getDropHighlightPlace() {
    return dropHighlightPlace;
}
