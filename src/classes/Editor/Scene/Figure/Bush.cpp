#include "Bush.hpp"

#include "classes/Editor/Scene/ResizeIndicator.hpp"

Bush::Bush(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : Figure(tileFactory, grid) {
    if (size < 1) {
        size = 1;
    }

    activeResizeIndicators = ResizeIndicator::LeftEdge | ResizeIndicator::RightEdge;

    this->size = size;

    auto begin = tileFactory->createStaticTile(2, 0);
    begin->setGrid(grid);
    begin->snapToGrid(pointOnGrid);
    pointOnGrid.x++;
    tiles.push_back(begin);

    for (int i=0; i<size; i++) {
        auto middle = tileFactory->createStaticTile(3, 0);
        middle->setGrid(grid);
        middle->snapToGrid(pointOnGrid);
        pointOnGrid.x++;
        tiles.push_back(middle);
    }

    auto end = tileFactory->createStaticTile(4, 0);
    end->setGrid(grid);
    end->snapToGrid(pointOnGrid);
    tiles.push_back(end);
}
