#include "Cloud.hpp"

#include <iostream>

#include <SFML/Graphics/Rect.hpp>

Cloud::Cloud(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : Figure (tileFactory, grid) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    generate(tileFactory, grid, size);
    reCreateIndicators();
}

void Cloud::generate(
    std::unique_ptr<TileFactory> &tileFactory,
    std::shared_ptr<Grid> &grid,
    sf::Uint8 size
) {
    auto beginBottom = tileFactory->createStaticTile(0, 8);
    beginBottom->setGrid(grid);
    beginBottom->snapToGrid(pointOnGrid);
    pointOnGrid.y--;
    tiles.push_back(beginBottom);

    auto beginTop = tileFactory->createStaticTile(0, 7);
    beginTop->setGrid(grid);
    beginTop->snapToGrid(pointOnGrid);
    pointOnGrid.x++;
    pointOnGrid.y++;
    tiles.push_back(beginTop);


    for (int i=0; i<size; i++) {
        auto middleBottom = tileFactory->createStaticTile(1, 8);
        middleBottom->setGrid(grid);
        middleBottom->snapToGrid(pointOnGrid);
        pointOnGrid.y--;
        tiles.push_back(middleBottom);

        auto middleTop = tileFactory->createStaticTile(1, 7);
        middleTop->setGrid(grid);
        middleTop->snapToGrid(pointOnGrid);
        pointOnGrid.x++;
        pointOnGrid.y++;
        tiles.push_back(middleTop);
    }

    auto endBottom = tileFactory->createStaticTile(2, 8);
    endBottom->setGrid(grid);
    endBottom->snapToGrid(pointOnGrid);
    pointOnGrid.y--;
    tiles.push_back(endBottom);

    auto endTop = tileFactory->createStaticTile(2, 7);
    endTop->setGrid(grid);
    endTop->snapToGrid(pointOnGrid);
    tiles.push_back(endTop);
}

void Cloud::draw(std::shared_ptr<sf::RenderWindow> window) {
    Figure::draw(window);

    if (isMouseOver() && !isDragging()) {
        leftIndicator->draw(window);
        rightIndicator->draw(window);
    }
}

void Cloud::rescale(std::unique_ptr<Scale> &scale) {
    Figure::rescale(scale);
    reCreateIndicators();

    leftIndicator->rescale(scale);
    rightIndicator->rescale(scale);
}

void Cloud::snapToGrid(sf::Vector2i pointOnGrid) {
    Figure::snapToGrid(pointOnGrid);
}

void Cloud::reCreateIndicators() {
    sf::Rect figureRect(getPosition(), sf::Vector2f(getSize()));

    leftIndicator = std::make_unique<ResizeIndicator>(
        figureRect, ResizeIndicator::IndicatorSide::Left, ResizeIndicator::MoveDirection::Horizontal, [=]() mutable {
            resizeToLeft();
        }
    );

    rightIndicator = std::make_unique<ResizeIndicator>(
        figureRect, ResizeIndicator::IndicatorSide::Right, ResizeIndicator::MoveDirection::Horizontal, [=]() mutable {
            resizeToRight();
        }
    );
}

void Cloud::resizeToLeft() {

}

void Cloud::resizeToRight() {

}

void Cloud::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    Figure::drop(animationPerformer);
    reCreateIndicators();
}
