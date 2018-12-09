#include "ButtonTile.hpp"

#include "classes/Infrastructure/Log.hpp"

ButtonTile::ButtonTile(sf::Sprite sprite, TileConfig config) : Tile(sprite, config) {

}

void ButtonTile::draw(std::shared_ptr<sf::RenderWindow> window) const {
    if (border.getSize().x > 0 && border.getSize().y > 0) {
        window->draw(border);
    }
    window->draw(sprite);
}

void ButtonTile::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    border.setFillColor(sf::Color(255, 255, 0));

    Log::out("ButtonTile MouseEnter");
}

void ButtonTile::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void ButtonTile::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    border.setFillColor(sf::Color(255, 255, 255));

    Log::out("ButtonTile MouseLeave");
}

bool ButtonTile::isMouseOver() const {
    return isMouseOverFlag;
}

void ButtonTile::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = true;

    Log::out("ButtonTile StartDrag");
}

void ButtonTile::drag(sf::Vector2f cursorPosition) {

}

void ButtonTile::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = false;

    Log::out("ButtonTile Drop");
}

bool ButtonTile::isDragging() const {
    return isDraggingFlag;
}

std::shared_ptr<DynamicTile> ButtonTile::cloneToDynamicTile(
    std::unique_ptr<TileFactory> &tileFactory, std::unique_ptr<Grid> &grid
) {
    auto tile = tileFactory->createDynamicTile(imagePosition.x, imagePosition.y, grid);
    return tile;
}
