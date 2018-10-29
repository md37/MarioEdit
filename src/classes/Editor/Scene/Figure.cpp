#include "Figure.hpp"

#include "classes/System/Cursor.hpp"
#include "classes/Editor/Exception/EmptyFigureFoundException.hpp"

Figure::Figure(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position) {
    this->tileFactory = tileFactory;
    this->grid = grid;
    this->position = position;
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
}

void Figure::createFrame() {
    auto thickness = grid->getLineThickness();
    auto size = this->getSize();

    frame.setSize(sf::Vector2f(size));
    frame.setOutlineThickness(thickness*4);
    frame.setOutlineColor(sf::Color(255, 255, 255, 128));
    frame.setFillColor(sf::Color(255, 255, 255, 20));

    updateFramePosition();

    isFrameCreated = true;
}

void Figure::updateFramePosition() {
    auto framePosition = getPosition();
    framePosition.y -= getSize().y;
    frame.setPosition(framePosition);
}

void Figure::rescale(std::shared_ptr<Scale> scale) {
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
}

void Figure::setGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}

void Figure::snapToGrid() {
    for (auto &tile : tiles) {
        tile->snapToGrid();
    }
}

void Figure::snapToGrid(sf::Vector2i pointOnGrid) {
    for (auto &tile : tiles) {
        tile->snapToGrid(pointOnGrid);
    }
}

bool Figure::isMouseOver() {
    return isMouseOverFlag;
}

void Figure::mouseEnter(std::shared_ptr<AnimationPerformer> animationPerformer) {
    isMouseOverFlag = true;
}

void Figure::mouseOver(std::shared_ptr<AnimationPerformer> animationPerformer) {

}

void Figure::mouseLeave(std::shared_ptr<AnimationPerformer> animationPerformer) {
    isMouseOverFlag = false;
    isFrameCreated = false;
}

sf::Vector2f Figure::getPosition() {
    auto point = grid->pointOnGridToPosition(sf::Vector2i(position));
    auto oneUnit = grid->pointOnGridToPosition(sf::Vector2i(1, 1));
    point.y += oneUnit.y;
    return point;
}

sf::Vector2u Figure::getSize() {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPosition().x+mostRightTile->getSize().x - mostLeftTile->getPosition().x;
    sf::Uint32 height = (mostBottomTile->getPosition().y+mostBottomTile->getSize().y) - mostTopTile->getPosition().y;
    return {width, height};
}

sf::Vector2i Figure::getPointOnGrid() {
    return position;
}

sf::Vector2u Figure::getSizeOnGrid() {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPointOnGrid().x - mostLeftTile->getPointOnGrid().x;
    sf::Uint32 height = mostBottomTile->getPointOnGrid().y - mostTopTile->getPointOnGrid().y;
    return {width+1, height+1};
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

void Figure::startDrag(std::shared_ptr<AnimationPerformer> animationPerformer) {
    isDraggingFlag = true;
    frame.setOutlineColor(sf::Color(255, 255, 0, 128));
    frame.setFillColor(sf::Color(255, 255, 0, 20));

    grid->turnHighlightOn(getSizeOnGrid());

    calculateDragOffset();
    recalculateHighlightPosition();
    moveTiles();
}

void Figure::calculateDragOffset() {
    auto cursorPosition = Cursor::getCurrentPosition();
    auto dragOffsetPartial = cursorPosition - getPosition();
    auto dragOffsetOnGrid = grid->positionToPointOnGrid(dragOffsetPartial);

    dragOffsetOnGrid = getPointOnGrid() - dragOffsetOnGrid;
    dragOffsetOnGrid.y--;
    dragOffset = getPosition() - grid->pointOnGridToPosition(dragOffsetOnGrid);
}

void Figure::drag() {
    recalculateHighlightPosition();

    moveTiles();
    updateFramePosition();
    frame.setPosition(grid->getHighlightPosition());
}

void Figure::recalculateHighlightPosition() {
    auto highlightPosition = Cursor::getCurrentPosition();
    highlightPosition.x -= dragOffset.x;
    highlightPosition.y -= dragOffset.y;

    grid->setHighlightPosition(highlightPosition);
}

void Figure::moveTiles() {
    auto cursorPosition = Cursor::getCurrentPosition();
    cursorPosition -= dragOffset;

    for (auto &tile : tiles) {

    }
}

void Figure::drop(std::shared_ptr<AnimationPerformer> animationPerformer) {
    isDraggingFlag = false;

    position = grid->getHighlightPointOnGrid();
    position.y += getSizeOnGrid().y-1;
    grid->turnHighlightOff();

    createFrame();
    frame.setOutlineColor(sf::Color(255, 255, 255, 128));
    frame.setFillColor(sf::Color(255, 255, 255, 20));
}
