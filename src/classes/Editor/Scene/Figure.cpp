#include "Figure.hpp"

#include <iostream>
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
    frame.setFillColor(sf::Color(255, 255, 255, 0));
    frame.setOutlineThickness(thickness*4);
    frame.setOutlineColor(sf::Color(255, 255, 255, 128));
    frame.setFillColor(sf::Color(255, 255, 255, 20));

    auto framePosition = this->getPosition();
    framePosition.y -= this->getSize().y;
    frame.setPosition(framePosition);
}

void Figure::rescale(std::shared_ptr<Scale> scale) {
    for (auto &tile : tiles) {
        tile->rescale(scale);
    }
}

void Figure::snapToGrid() {
    for (auto &tile : tiles) {
        tile->snapToGrid();
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
}

sf::Vector2f Figure::getPosition() {
    auto point = grid->pointOnGridToPosition(sf::Vector2u(position));
    auto oneUnit = grid->pointOnGridToPosition(sf::Vector2u(1, 1));
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
