#include "Cloud.hpp"

#include <SFML/Graphics/Rect.hpp>

Cloud::Cloud(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : Figure (tileFactory, grid
) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    generate(tileFactory, grid, size);
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
