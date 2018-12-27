#include "Figure.hpp"

#include "classes/Infrastructure/Log.hpp"
#include "classes/Editor/Exception/EmptyFigureFoundException.hpp"

Figure::Figure(std::unique_ptr<TileFactory> &tileFactory) : tileFactory(tileFactory) {

}

void Figure::draw(std::shared_ptr<sf::RenderWindow> window) const {
    for (auto &tile : tiles) {
        tile->draw(window);
    }
}

void Figure::rescale(std::unique_ptr<Scale> &scale) {
    Log::out("Rescaling figure");
    grid->rescale(scale);
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
    snapToGrid();
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

sf::Vector2u Figure::getSize() const {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPosition().x + mostRightTile->getSize().x - mostLeftTile->getPosition().x;
    sf::Uint32 height = (mostBottomTile->getPosition().y + mostBottomTile->getSize().y) - mostTopTile->getPosition().y;
    return {width, height};
}

sf::Vector2f Figure::getPosition() const {
    return position;
}

sf::Rect<float> Figure::getRect() const {
    return sf::Rect<float>(getPosition(), sf::Vector2f(getSize()));
}

sf::Vector2i Figure::getPointOnGrid() const {
    return grid->positionToPointOnGrid(position);
}

sf::Vector2u Figure::getSizeOnGrid() const {
    auto mostLeftTile = findMostLeftTile();
    auto mostRightTile = findMostRightTile();
    auto mostTopTile = findMostTopTile();
    auto mostBottomTile = findMostBottomTile();

    sf::Uint32 width = mostRightTile->getPointOnGrid().x - mostLeftTile->getPointOnGrid().x;
    sf::Uint32 height = mostBottomTile->getPointOnGrid().y - mostTopTile->getPointOnGrid().y;
    return {width + 1, height + 1};
}

std::shared_ptr<StaticTile> Figure::findMostLeftTile() const {
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

std::shared_ptr<StaticTile> Figure::findMostRightTile() const {
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

std::shared_ptr<StaticTile> Figure::findMostTopTile() const {
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

std::shared_ptr<StaticTile> Figure::findMostBottomTile() const {
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