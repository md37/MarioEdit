#include "CloudGenerator.hpp"

CloudGenerator::CloudGenerator(
        std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size
) : AbstractFigureGenerator(tileFactory, grid, size) {

}

std::vector<std::shared_ptr<StaticTile>> CloudGenerator::generate(sf::Vector2i pointOnGrid) {
    std::vector<std::shared_ptr<StaticTile>> tiles;

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

    return tiles;
}
