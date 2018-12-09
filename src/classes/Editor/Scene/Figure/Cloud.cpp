#include "Cloud.hpp"

#include <SFML/Graphics/Rect.hpp>
#include "classes/Infrastructure/Log.hpp"

Cloud::Cloud(std::unique_ptr<TileFactory> &tileFactory, std::unique_ptr<Grid>& grid, sf::Uint8 size) : Figure (tileFactory, grid)
{
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    generate();
}

void Cloud::generate() {
    auto pointOnGrid = this->pointOnGrid;

    auto beginBottom = tileFactory->createStaticTile(0, 8, grid);
    beginBottom->snapToGrid(pointOnGrid);
    pointOnGrid.y--;
    tiles.push_back(beginBottom);

    auto beginTop = tileFactory->createStaticTile(0, 7, grid);
    beginTop->snapToGrid(pointOnGrid);
    pointOnGrid.x++;
    pointOnGrid.y++;
    tiles.push_back(beginTop);


    for (int i=0; i<size; i++) {
        auto middleBottom = tileFactory->createStaticTile(1, 8, grid);
        middleBottom->snapToGrid(pointOnGrid);
        pointOnGrid.y--;
        tiles.push_back(middleBottom);

        auto middleTop = tileFactory->createStaticTile(1, 7, grid);
        middleTop->snapToGrid(pointOnGrid);
        pointOnGrid.x++;
        pointOnGrid.y++;
        tiles.push_back(middleTop);
    }

    auto endBottom = tileFactory->createStaticTile(2, 8, grid);
    endBottom->snapToGrid(pointOnGrid);
    pointOnGrid.y--;
    tiles.push_back(endBottom);

    auto endTop = tileFactory->createStaticTile(2, 7, grid);
    endTop->snapToGrid(pointOnGrid);
    tiles.push_back(endTop);
}

void Cloud::changeVariant(sf::Uint8 variant) {
    if (variant < 1 || variant > 2 || variant == size) {
        return;
    }

    Log::out("Change Figure Variant");

    size = variant;
    tiles.clear();

    pointOnGrid = grid->getHighlight()->getPointOnGrid();
    pointOnGrid.y++;
    position = grid->getHighlight()->getPosition();

    generate();

    grid->turnHighlightOn(getSizeOnGrid());
    resetFrame();
}
