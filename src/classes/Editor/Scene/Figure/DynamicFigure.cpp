#include "DynamicFigure.hpp"

#include "classes/Infrastructure/Log.hpp"
#include "classes/Infrastructure/Collision.hpp"
#include "classes/Infrastructure/Cursor.hpp"
#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Exception/EmptyFigureFoundException.hpp"

DynamicFigure::DynamicFigure(std::unique_ptr<TileFactory> &tileFactory) : tileFactory(tileFactory) {
    this->grid = grid;
}

void DynamicFigure::draw(std::shared_ptr<sf::RenderWindow> window) const {
    for (auto &tile : tiles) {
        tile->draw(window);
    }
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

void DynamicFigure::rescale(std::unique_ptr<Scale> &scale) {
    Log::out("Rescaling figure");
    grid->rescale(scale);
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
    snapToGrid();
}

void DynamicFigure::snapToGrid() {
    this->snapToGrid(pointOnGrid);
}

void DynamicFigure::snapToGrid(sf::Vector2i pointOnGrid) {
    this->pointOnGrid = pointOnGrid;
    this->position = grid->pointOnGridToPosition(pointOnGrid);

    auto mostLeftTile = findMostLeftTile();
    auto mostTopTile = findMostTopTile();

    sf::Vector2i diff = {
        pointOnGrid.x - mostLeftTile->getPointOnGrid().x,
        pointOnGrid.y - mostTopTile->getPointOnGrid().y
    };

    for (auto &tile : tiles) {
        auto currentPointOnGrid = tile->getPointOnGrid();
        tile->snapToGrid(currentPointOnGrid + diff);
    }
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

sf::Vector2f DynamicFigure::getPosition() const {
    return position;
}

sf::Vector2u DynamicFigure::getSize() const {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPosition().x + mostRightTile->getSize().x - mostLeftTile->getPosition().x;
    sf::Uint32 height = (mostBottomTile->getPosition().y + mostBottomTile->getSize().y) - mostTopTile->getPosition().y;
    return {width, height};
}

sf::Vector2i DynamicFigure::getPointOnGrid() const {
    return grid->positionToPointOnGrid(position);
}

sf::Vector2u DynamicFigure::getSizeOnGrid() const {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPointOnGrid().x - mostLeftTile->getPointOnGrid().x;
    sf::Uint32 height = mostBottomTile->getPointOnGrid().y - mostTopTile->getPointOnGrid().y;
    return {width + 1, height + 1};
}

std::shared_ptr<StaticTile> DynamicFigure::findMostLeftTile() const {
    if (tiles.size() == 0) {
        EmptyFigureFoundException e;
        throw e;
    }

    auto mostLeftTile = tiles.at(0);
    auto mostLeftTilePosition = mostLeftTile->getPosition();
    for (auto &tile: tiles) {
        auto tilePosition = tile->getPosition();
        if (tilePosition.x < mostLeftTilePosition.x) {
            mostLeftTile = tile;
            mostLeftTilePosition = tilePosition;
        }
    }
    return mostLeftTile;
}

std::shared_ptr<StaticTile> DynamicFigure::findMostRightTile() const {
    if (tiles.size() == 0) {
        EmptyFigureFoundException e;
        throw e;
    }

    auto mostRightTile = tiles.at(0);
    auto mostRightTilePosition = mostRightTile->getPosition();
    for (auto &tile: tiles) {
        auto tilePosition = tile->getPosition();
        if (tilePosition.x > mostRightTilePosition.x) {
            mostRightTile = tile;
            mostRightTilePosition = tilePosition;
        }
    }
    return mostRightTile;
}

std::shared_ptr<StaticTile> DynamicFigure::findMostTopTile() const {
    if (tiles.size() == 0) {
        EmptyFigureFoundException e;
        throw e;
    }

    auto mostTopTile = tiles.at(0);
    auto mostTopTilePosition = mostTopTile->getPosition();
    for (auto &tile: tiles) {
        auto tilePosition = tile->getPosition();
        if (tilePosition.y < mostTopTilePosition.y) {
            mostTopTile = tile;
            mostTopTilePosition = tilePosition;
        }
    }
    return mostTopTile;
}

std::shared_ptr<StaticTile> DynamicFigure::findMostBottomTile() const {
    if (tiles.size() == 0) {
        EmptyFigureFoundException e;
        throw e;
    }

    auto mostBottomTile = tiles.at(0);
    auto mostBottomTilePosition = mostBottomTile->getPosition();
    for (auto &tile: tiles) {
        auto tilePosition = tile->getPosition();
        if (tilePosition.y > mostBottomTilePosition.y) {
            mostBottomTile = tile;
            mostBottomTilePosition = tilePosition;
        }
    }
    return mostBottomTile;
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

sf::Rect<float> DynamicFigure::getRect() const {
    return sf::Rect<float>(getPosition(), sf::Vector2f(getSize()));
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
