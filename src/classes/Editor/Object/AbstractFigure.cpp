#include "AbstractFigure.hpp"

#include "classes/Infrastructure/Log.hpp"
#include "classes/Editor/Exception/EmptyFigureFoundException.hpp"

AbstractFigure::AbstractFigure(std::unique_ptr<TileFactory> &tileFactory) : tileFactory(tileFactory) {

}

void AbstractFigure::draw(std::shared_ptr<sf::RenderWindow> window) const {
    for (auto &tile : tiles) {
        tile->draw(window);
    }
}

void AbstractFigure::rescale(std::unique_ptr<Scale> &scale) {
    Log::out("Rescaling figure");
    grid->rescale(scale);
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
    snapToGrid();
}

void AbstractFigure::snapToGrid() {
    this->snapToGrid(pointOnGrid);
}

void AbstractFigure::snapToGrid(sf::Vector2i pointOnGrid) {
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

sf::Vector2u AbstractFigure::getSize() const {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPosition().x + mostRightTile->getSize().x - mostLeftTile->getPosition().x;
    sf::Uint32 height = (mostBottomTile->getPosition().y + mostBottomTile->getSize().y) - mostTopTile->getPosition().y;
    return {width, height};
}

sf::Vector2f AbstractFigure::getPosition() const {
    return position;
}

sf::Rect<float> AbstractFigure::getRect() const {
    return sf::Rect<float>(getPosition(), sf::Vector2f(getSize()));
}

sf::Vector2i AbstractFigure::getPointOnGrid() const {
    return grid->positionToPointOnGrid(position);
}

sf::Vector2u AbstractFigure::getSizeOnGrid() const {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPointOnGrid().x - mostLeftTile->getPointOnGrid().x;
    sf::Uint32 height = mostBottomTile->getPointOnGrid().y - mostTopTile->getPointOnGrid().y;
    return {width + 1, height + 1};
}

std::shared_ptr<StaticTile> AbstractFigure::findMostLeftTile() const {
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

std::shared_ptr<StaticTile> AbstractFigure::findMostRightTile() const {
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

std::shared_ptr<StaticTile> AbstractFigure::findMostTopTile() const {
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

std::shared_ptr<StaticTile> AbstractFigure::findMostBottomTile() const {
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