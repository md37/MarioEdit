#include "TileButton.hpp"

#include "classes/Infrastructure/Log.hpp"

TileButton::TileButton(sf::Sprite sprite, TileConfig config) : AbstractTile(sprite, config) {

}

void TileButton::draw(std::shared_ptr<sf::RenderWindow> window) const {
    if (border.getSize().x > 0 && border.getSize().y > 0) {
        window->draw(border);
    }
    window->draw(sprite);
}

void TileButton::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    border.setFillColor(sf::Color(255, 255, 0));

    Log::out("ButtonTile MouseEnter");
}

void TileButton::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void TileButton::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    border.setFillColor(sf::Color(255, 255, 255));

    Log::out("ButtonTile MouseLeave");
}

bool TileButton::isMouseOver() const {
    return isMouseOverFlag;
}

void TileButton::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = true;

    Log::out("ButtonTile StartDrag");
}

void TileButton::drag(sf::Vector2f cursorPosition) {

}

void TileButton::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = false;

    Log::out("ButtonTile Drop");
}

bool TileButton::isDragging() const {
    return isDraggingFlag;
}

std::shared_ptr<DynamicTile> TileButton::cloneToDynamicTile(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> &grid
) {
    auto tile = tileFactory->createDynamicTile(imagePosition.x, imagePosition.y, grid);
    return tile;
}
