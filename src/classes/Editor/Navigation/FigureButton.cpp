#include <classes/Editor/ObjectRegistry.hpp>
#include <classes/Editor/Scene/Figure/Type/Cloud.hpp>
#include "FigureButton.hpp"

#include "classes/Infrastructure/Log.hpp"

FigureButton::FigureButton(
    sf::Vector2f position,
    std::unique_ptr<TileFactory> &tileFactory,
    std::shared_ptr<Grid> grid,
    std::shared_ptr<AbstractFigureGenerator> generator,
    sf::Vector2i pointOnGrid
) : StaticFigure(tileFactory) {
    this->position = position;
    this->grid = grid;
    this->generator = generator;
    this->pointOnGrid = pointOnGrid;

    background.setFillColor(backgroundColor);
    generator->generate(pointOnGrid, 1);
}

void FigureButton::draw(std::shared_ptr<sf::RenderWindow> window) const {
    if (isMouseOverFlag) {
        window->draw(background);
    }
    for (auto &tile: tiles) {
        tile->draw(window);
    }
}

void FigureButton::rescale(std::unique_ptr<Scale> &newScale) {
    Log::out("Rescaling figure button");

    position *= newScale->getRatio();
    borderCutTop *= newScale->getRatio();
    borderCutLeft *= newScale->getRatio();
    borderCutBottom *= newScale->getRatio();
    borderCutRight *= newScale->getRatio();

    grid->rescale(newScale);
    rescaleTiles(newScale);
    rescaleBackground(newScale);
}

void FigureButton::rescaleTiles(std::unique_ptr<Scale> &newScale) {
    tiles = generator->generate(pointOnGrid, 1);
    for (auto &tile: tiles) {
        tile->setScalePromotion(grid->getScale());
        tile->rescale(newScale);
        tile->snapToGrid();
    }
}

void FigureButton::rescaleBackground(const std::unique_ptr<Scale> &newScale) {
    borderSize *= newScale->getRatio();
    auto borderSquareSize = sf::Vector2f(getSize());
    borderSquareSize.x += 2 * borderSize;
    borderSquareSize.y += 2 * borderSize;
    background.setSize(borderSquareSize);

    auto borderSquarePosition = sf::Vector2f(getPosition());
    borderSquarePosition.x -= borderSize;
    borderSquarePosition.y -= borderSize;
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

sf::Vector2f FigureButton::getPosition() const {
    auto position = this->position;
    position.x += borderCutLeft;
    position.y += borderCutTop;
    return position;
}

sf::Vector2u FigureButton::getSize() const {
    auto size = AbstractFigure::getSize();
    size.x -= borderCutLeft+borderCutRight;
    size.y -= borderCutTop+borderCutBottom;
    return size;
}

std::shared_ptr<DynamicFigure> FigureButton::cloneToDynamicFigure(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid
) {
    Log::out("Cloning to dynamic figure");

    std::vector<std::shared_ptr<StaticTile>> tilesCopy;
    for (auto &tile: tiles) {
        auto coords = tile->getImageCoords();
        std::shared_ptr<StaticTile> tileCopy = tileFactory->createStaticTile(coords.x, coords.y, grid);
        tileCopy->snapToGrid(tile->getPointOnGrid());
        tilesCopy.push_back(tileCopy);
    }
    std::shared_ptr<DynamicFigure> figure = std::make_shared<DynamicFigure>(tileFactory, tilesCopy);
    figure->changeGrid(grid);

    ObjectRegistry::add(figure);
    return figure;
}
