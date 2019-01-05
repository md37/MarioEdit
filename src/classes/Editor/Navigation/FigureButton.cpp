#include "FigureButton.hpp"

#include "classes/Infrastructure/Log.hpp"

FigureButton::FigureButton(
    sf::Vector2f position,
    std::unique_ptr<TileFactory> &tileFactory,
    std::shared_ptr<Grid> grid,
    std::shared_ptr<AbstractFigureGenerator> generator
) : StaticFigure(tileFactory) {
    this->position = position;
    this->grid = grid;
    this->generator = generator;
    background.setFillColor(backgroundColor);
}

void FigureButton::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(background);
    for (auto &tile: tiles) {
        tile->draw(window);
    }
}

void FigureButton::rescale(std::unique_ptr<Scale> &newScale) {
    Log::out("Rescaling figure button");

    position *= newScale->getRatio();
    grid->rescale(newScale);
    rescaleTiles(newScale);
    rescaleBackground(newScale);
}

void FigureButton::rescaleTiles(std::unique_ptr<Scale> &newScale) {
    tiles = generator->generate(pointOnGrid);
    for (auto &tile: tiles) {
        tile->setScalePromotion(grid->getScale());
        tile->rescale(newScale);
        tile->snapToGrid();
    }
}

void FigureButton::rescaleBackground(const std::unique_ptr<Scale> &newScale) {
    borderCutTop *= newScale->getRatio();
    borderCutLeft *= newScale->getRatio();
    borderCutBottom *= newScale->getRatio();
    borderCutRight *= newScale->getRatio();

    borderSize *= newScale->getRatio();
    auto borderSquareSize = sf::Vector2f(getSize());
    borderSquareSize.x += 2 * borderSize;
    borderSquareSize.x -= borderCutLeft+borderCutRight;
    borderSquareSize.y += 2 * borderSize;
    borderSquareSize.y -= borderCutTop+borderCutBottom;
    background.setSize(borderSquareSize);

    auto borderSquarePosition = sf::Vector2f(position);
    borderSquarePosition.x -= borderSize;
    borderSquarePosition.x += borderCutLeft;
    borderSquarePosition.y -= borderSize;
    borderSquarePosition.y += borderCutTop;
    background.setPosition(borderSquarePosition);
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

void FigureButton::cutBorder(float top, float left, float bottom, float right) {
    borderCutTop = top;
    borderCutLeft = left;
    borderCutBottom = bottom;
    borderCutRight = right;
}
