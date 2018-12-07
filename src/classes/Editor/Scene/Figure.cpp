#include "Figure.hpp"

#include "classes/Infrastructure/Log.hpp"
#include "classes/Infrastructure/Collision.hpp"
#include "classes/Infrastructure/Cursor.hpp"
#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Scene/ResizeIndicator.hpp"
#include "classes/Editor/Exception/EmptyFigureFoundException.hpp"

Figure::Figure(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid) : tileFactory(tileFactory) {
    this->grid = grid;
}

void Figure::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (auto &tile : tiles) {
        tile->draw(window);
    }
}

void Figure::drawFrame(std::shared_ptr<sf::RenderWindow> window) {
    if (!isFrameCreated) {
        createFrame();
    }
    window->draw(frame);

    if (!isDragging()) {
        if (!resizeIndicatorsGenerated) {
            reCreateResizeIndicators();
        }
        for (auto &indicator: resizeIndicators) {
            indicator->draw(window);
        }
    }
}

void Figure::reCreateResizeIndicators() {
    auto indicatorsCount = 8;

    resizeIndicators.clear();
    for (int i=0; i<indicatorsCount; i++) {
        auto indicatorSide = (ResizeIndicator::IndicatorSide )(1 << i);
        bool isIndicatorActive = (activeResizeIndicators & indicatorSide) != 0;

        auto figureRect = getRect();
        auto callback = [=]() mutable {};
        auto indicator = std::make_shared<ResizeIndicator>(
            figureRect, indicatorSide, callback, isIndicatorActive
        );
        resizeIndicators.push_back(indicator);
    }
    resizeIndicatorsGenerated = true;
}

void Figure::createFrame() {
    auto size = this->getSize();

    frame.setSize(sf::Vector2f(size));
    frame.setOutlineThickness(0);
    frame.setFillColor(frameColorNormal);

    updateFramePosition();

    isFrameCreated = true;
}

void Figure::updateFramePosition() {
    auto framePosition = getPosition();
    frame.setPosition(framePosition);
}

void Figure::rescale(std::unique_ptr<Scale> &scale) {
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
    snapToGrid();

    reCreateResizeIndicators();
    for (auto &indicator : resizeIndicators) {
        indicator->rescale(scale);
    }
}

void Figure::setGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}

void Figure::snapToGrid() {
    this->snapToGrid(pointOnGrid);
}

void Figure::snapToGrid(sf::Vector2i pointOnGrid) {
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

bool Figure::isMouseOver() {
    return isMouseOverFlag;
}

void Figure::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
}

void Figure::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void Figure::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
    isFrameCreated = false;
}

sf::Vector2f Figure::getPosition() {
    return position;
}

sf::Vector2u Figure::getSize() {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPosition().x + mostRightTile->getSize().x - mostLeftTile->getPosition().x;
    sf::Uint32 height = (mostBottomTile->getPosition().y + mostBottomTile->getSize().y) - mostTopTile->getPosition().y;
    return {width, height};
}

sf::Vector2i Figure::getPointOnGrid() {
    return grid->positionToPointOnGrid(position);
}

sf::Vector2u Figure::getSizeOnGrid() {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPointOnGrid().x - mostLeftTile->getPointOnGrid().x;
    sf::Uint32 height = mostBottomTile->getPointOnGrid().y - mostTopTile->getPointOnGrid().y;
    return {width + 1, height + 1};
}

std::shared_ptr<StaticTile> Figure::findMostLeftTile() {
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

std::shared_ptr<StaticTile> Figure::findMostRightTile() {
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

std::shared_ptr<StaticTile> Figure::findMostTopTile() {
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

std::shared_ptr<StaticTile> Figure::findMostBottomTile() {
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

bool Figure::isDragging() {
    return isDraggingFlag;
}

void Figure::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Log::line();
    Log::out("Drag figure");
    isDraggingFlag = true;
    frame.setFillColor(frameColorNormal);

    grid->turnHighlightOn(getSizeOnGrid());

    calculateDragOffset(cursorPosition);
    recalculateHighlightPosition(cursorPosition);
    moveTiles(position);
}

void Figure::calculateDragOffset(sf::Vector2f cursorPosition) {
    dragOffset = cursorPosition - getPosition();

    auto dragOffsetOnGrid = grid->positionToPointOnGrid(dragOffset);
    dragOffsetOnGrid = getPointOnGrid() - dragOffsetOnGrid;
    dragOffsetForHighlight = getPosition() - grid->pointOnGridToPosition(dragOffsetOnGrid);
}

void Figure::drag(sf::Vector2f cursorPosition) {
    auto prevHighlightPosition = grid->getHighlightPosition();

    recalculateHighlightPosition(cursorPosition);
    recalculateFramePosition(cursorPosition);
    moveTiles(position);
    position = frame.getPosition();

    bool isCollision = checkForCollisions();
    if (isCollision) {
        frame.setFillColor(frameColorError);
        grid->setHighlightPosition(prevHighlightPosition);
    } else {
        frame.setFillColor(frameColorNormal);
    }

    moveResizeIndicators();
}

bool Figure::checkForCollisions() {
    Collision collision(getRect());
    auto figures = ObjectRegistry::getFigures();
    for (auto figure: figures) {
        bool isMe = figure->getPosition() == getPosition();
        if (isMe) {
            continue;
        }

        auto figureRect = figure->getRect();
        if (collision.checkCollision(figureRect) != Collision::None) {
            Log::line();
            Log::out("Collision detected");
            Log::out(getRect(), "Current rect");
            Log::out(figureRect, "Figure rect");

            return true;
        }
    }
    return false;
}

sf::Rect<float> Figure::getRect() {
    return sf::Rect<float>(getPosition(), sf::Vector2f(getSize()));
}

void Figure::recalculateHighlightPosition(sf::Vector2f cursorPosition) {
    auto highlightPosition = cursorPosition;
    highlightPosition -= dragOffsetForHighlight;

    grid->setHighlightPosition(highlightPosition);
}

void Figure::recalculateFramePosition(sf::Vector2f cursorPosition) {
    auto newFramePosition = cursorPosition;
    newFramePosition -= dragOffset;
    frame.setPosition(newFramePosition);
}

void Figure::moveTiles(sf::Vector2f prevPosition) {
    auto currentPosition = frame.getPosition();
    auto positionDiff = currentPosition - prevPosition;

    for (auto &tile : tiles) {
        auto tileCurrentPosition = tile->getPosition();
        tileCurrentPosition += positionDiff;
        tile->setPosition(tileCurrentPosition);
    }
}

void Figure::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Log::line();
    Log::out("Drop figure");

    isDraggingFlag = false;

    pointOnGrid = grid->getHighlightPointOnGrid();
    position = grid->pointOnGridToPosition(pointOnGrid);
    grid->turnHighlightOff();

    createFrame();
    snapToGrid();
    dragOffset = {0.0f, 0.0f};
    dragOffsetForHighlight = {0.0f, 0.0f};

    moveResizeIndicators();
}

void Figure::moveResizeIndicators() {
    for (auto &indicator : resizeIndicators) {
        indicator->setFigureArea(getRect());
        indicator->recalculatePosition();
    }
}
