#include "DynamicFigure.hpp"

#include "classes/Infrastructure/Log.hpp"
#include "classes/Infrastructure/Collision.hpp"
#include "classes/Infrastructure/Cursor.hpp"
#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Infrastructure/Collision.hpp"

DynamicFigure::DynamicFigure(std::unique_ptr<TileFactory> &tileFactory) : Figure(tileFactory) {

}

void DynamicFigure::drawFrame(std::shared_ptr<sf::RenderWindow> window) {
    if (!isFrameCreated) {
        resetFrame();
    }
    window->draw(frame);
}

void DynamicFigure::resetFrame() {
    auto size = this->getSize();

    frame.setSize(sf::Vector2f(size));
    frame.setOutlineThickness(0);
    frame.setFillColor(frameColorNormal);

    updateFramePosition();

    isFrameCreated = true;
}

void DynamicFigure::updateFramePosition() {
    auto framePosition = getPosition();
    frame.setPosition(framePosition);
}

bool DynamicFigure::isMouseOver() const {
    return isMouseOverFlag;
}

void DynamicFigure::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;

    Log::out("Figure MouseEnter");
}

void DynamicFigure::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void DynamicFigure::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
    isFrameCreated = false;

    Log::out("Figure MouseLeave");
}

bool DynamicFigure::isDragging() const {
    return isDraggingFlag;
}

void DynamicFigure::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Log::out("Figure StartDrag");
    isDraggingFlag = true;
    frame.setFillColor(frameColorNormal);

    grid->turnHighlightOn(getSizeOnGrid());

    calculateDragOffset(cursorPosition);
    recalculateHighlightPosition(cursorPosition);
    moveTiles(position);
}

void DynamicFigure::calculateDragOffset(sf::Vector2f cursorPosition) {
    dragOffset = cursorPosition - getPosition();

    auto dragOffsetOnGrid = grid->positionToPointOnGrid(dragOffset);
    dragOffsetOnGrid = getPointOnGrid() - dragOffsetOnGrid;
    dragOffsetForHighlight = getPosition() - grid->pointOnGridToPosition(dragOffsetOnGrid);
}

void DynamicFigure::drag(sf::Vector2f cursorPosition) {
    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        auto prevHighlightPosition = highlight->getPosition();

        recalculateHighlightPosition(cursorPosition);
        recalculateFramePosition(cursorPosition);
        moveTiles(position);
        position = frame.getPosition();

        bool isCollision = checkForCollisions();
        if (isCollision) {
            frame.setFillColor(frameColorError);
            highlight->setPosition(prevHighlightPosition);
        } else {
            frame.setFillColor(frameColorNormal);
        }
    }
}

bool DynamicFigure::checkForCollisions() {
    Collision collision(getRect());
    auto figures = ObjectRegistry::getFigures();
    for (auto figure: figures) {
        bool isMe = figure->getPosition() == getPosition();
        if (isMe) {
            continue;
        }

        auto figureRect = figure->getRect();
        if (collision.checkCollision(figureRect) != Collision::None) {
            Log::out("Collision detected");
            Log::turnOnAutoLine(false);
            Log::out(getRect(), "Current rect");
            Log::out(figureRect, "Figure rect");
            Log::turnOnAutoLine(true);

            return true;
        }
    }
    return false;
}

void DynamicFigure::recalculateHighlightPosition(sf::Vector2f cursorPosition) const {
    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        auto highlightPosition = cursorPosition;
        highlightPosition -= dragOffsetForHighlight;

        highlight->setPosition(highlightPosition);
    }
}

void DynamicFigure::recalculateFramePosition(sf::Vector2f cursorPosition) {
    auto newFramePosition = cursorPosition;
    newFramePosition -= dragOffset;
    frame.setPosition(newFramePosition);
}

void DynamicFigure::moveTiles(sf::Vector2f prevPosition) {
    auto currentPosition = frame.getPosition();
    auto positionDiff = currentPosition - prevPosition;

    for (auto &tile : tiles) {
        auto tileCurrentPosition = tile->getPosition();
        tileCurrentPosition += positionDiff;
        tile->setPosition(tileCurrentPosition);
    }
}

void DynamicFigure::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Log::out("Figure Drop");

    isDraggingFlag = false;

    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        pointOnGrid = highlight->getPointOnGrid();
        position = grid->pointOnGridToPosition(pointOnGrid);
        grid->turnHighlightOff();
    }

    resetFrame();
    snapToGrid();
    dragOffset = {0.0f, 0.0f};
    dragOffsetForHighlight = {0.0f, 0.0f};
}

void DynamicFigure::changeGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}
