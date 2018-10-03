#include "ButtonTile.hpp"

ButtonTile::ButtonTile(sf::Sprite sprite, TileConfig config) : Tile(sprite, config) {

}

void ButtonTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    if (border.getSize().x > 0 && border.getSize().y > 0) {
        window->draw(border);
    }
    window->draw(sprite);
}

void ButtonTile::mouseEnter(AnimationPerformer& animationPerformer) {
    border.setFillColor(sf::Color(255, 255, 0));
}

void ButtonTile::mouseOver(AnimationPerformer& animationPerformer) {

}

void ButtonTile::mouseLeave(AnimationPerformer& animationPerformer) {
    border.setFillColor(sf::Color(255, 255, 255));
}

bool ButtonTile::isMouseOver() {
    return isMouseOverFlag;
}

void ButtonTile::startDrag(AnimationPerformer& animationPerformer) {
    isDraggingFlag = true;
}

void ButtonTile::drag(AnimationPerformer& animationPerformer) {

}

void ButtonTile::drop(AnimationPerformer& animationPerformer) {
    isDraggingFlag = false;
}

bool ButtonTile::isDragging() {
    return isDraggingFlag;
}

std::shared_ptr<DynamicTile> ButtonTile::cloneToDynamicTile(std::shared_ptr<TileFactory> tileFactory) {
    auto tile = tileFactory->createDynamicTile(imagePosition.x, imagePosition.y);
    return tile;
}
