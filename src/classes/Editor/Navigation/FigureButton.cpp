#include "FigureButton.hpp"

#include "classes/Infrastructure/Log.hpp"

FigureButton::FigureButton(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, std::shared_ptr<AbstractFigureGenerator> generator
) : StaticFigure(tileFactory) {
    this->grid = grid;
    this->generator = generator;
}

void FigureButton::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(border);
    for (auto &tile: tiles) {
        tile->draw(window);
    }
}

void FigureButton::rescale(std::unique_ptr<Scale> &newScale) {
    Log::out("Rescaling figure button");

    tiles = generator->generate(pointOnGrid);
    AbstractFigure::rescale(newScale);

    auto newBorderSize = borderSize * newScale->getCurrent();
    auto borderSquareSize = sf::Vector2f(getSize());
    borderSquareSize.x += 2 * newBorderSize;
    borderSquareSize.y += 2 * newBorderSize;
    border.setSize(borderSquareSize);

    auto borderSquarePosition = sf::Vector2f(position * newScale->getRatio());
    borderSquarePosition.x -= newBorderSize;
    borderSquarePosition.y -= newBorderSize;
    border.setPosition(borderSquarePosition);
}

bool FigureButton::isMouseOver() const {
    return isMouseOverFlag;
}

void FigureButton::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
}

void FigureButton::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void FigureButton::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
}

bool FigureButton::isDragging() const {
    return isDraggingFlag;
}

void FigureButton::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = true;
}

void FigureButton::drag(sf::Vector2f cursorPosition) {

}

void FigureButton::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = false;
}