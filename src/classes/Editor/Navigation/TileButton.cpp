#include "TileButton.hpp"

#include "classes/Infrastructure/Log.hpp"

TileButton::TileButton(sf::Sprite sprite, TileConfig config) : AbstractTile(sprite, config) {

}

void TileButton::draw(std::shared_ptr<sf::RenderWindow> window) const {
    if (background.getSize().x > 0 && background.getSize().y > 0) {
        window->draw(background);
    }
    window->draw(sprite);
}

void TileButton::rescale(std::unique_ptr<Scale> &newScale) {
    Log::out("Rescaling tile button");
    AbstractTile::rescale(newScale);

    auto newBorderSize = borderSize * newScale->getCurrent();
    auto borderSquareSize = sf::Vector2f(getSize());
    borderSquareSize.x += 2 * newBorderSize;
    borderSquareSize.y += 2 * newBorderSize;
    background.setSize(borderSquareSize);

    auto borderSquarePosition = sf::Vector2f(getPosition());
    borderSquarePosition.x -= newBorderSize;
    borderSquarePosition.y -= newBorderSize;
    background.setPosition(borderSquarePosition);
}

void TileButton::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    background.setFillColor(sf::Color(255, 255, 0));

    Log::out("ButtonTile MouseEnter");
}

void TileButton::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void TileButton::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    background.setFillColor(sf::Color(255, 255, 255));

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
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid
) {
    auto tile = tileFactory->createDynamicTile(imagePosition.x, imagePosition.y, grid);
    return tile;
}
