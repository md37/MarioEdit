#include "ButtonTile.hpp"

ButtonTile::ButtonTile(sf::Sprite sprite, TileConfig config) : Tile(sprite, config) {

}

void ButtonTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    if (border.getSize().x > 0 && border.getSize().y > 0) {
        window->draw(border);
    }
    window->draw(sprite);
}

void ButtonTile::mouseEnter() {

}

void ButtonTile::mouseOver() {

}

void ButtonTile::mouseLeave() {

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
