#include "ButtonTile.hpp"

ButtonTile::ButtonTile(sf::Sprite sprite, TileConfig config) : Tile(sprite, config) {
    highlightAnimation = std::make_shared<HighlightButtonAnimation>(this);
    undoHighlightAnimation = std::make_shared<UndoHighlightButtonAnimation>(this);
    createBorder();
}

void ButtonTile::createBorder() {

}

void ButtonTile::mouseEnter() {
    isMouseOverFlag = true;
    if (undoHighlightAnimation->isRunning()) {
        undoHighlightAnimation->stop();
    }
    if (!highlightAnimation->isRunning()) {
        highlightAnimation->run();
    }
}

void ButtonTile::mouseOver() {

}

void ButtonTile::mouseLeave() {
    isMouseOverFlag = false;
    if (highlightAnimation->isRunning()) {
        highlightAnimation->stop();
    }
    if (!undoHighlightAnimation->isRunning()) {
        undoHighlightAnimation->run();
    }
}

bool ButtonTile::isMouseOver() {
    return isMouseOverFlag;
}

void ButtonTile::startDrag() {
    isDraggingFlag = true;
}

void ButtonTile::drag() {

}

void ButtonTile::drop() {
    isDraggingFlag = false;
}

bool ButtonTile::isDragging() {
    return isDraggingFlag;
}

void ButtonTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(border);
    window->draw(sprite);
}
