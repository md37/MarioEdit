#include "HillGenerator.hpp"

#include "classes/Infrastructure/Log.hpp"

HillGenerator::HillGenerator(
        std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid
) : AbstractFigureGenerator(tileFactory, grid) {

}

std::vector<std::shared_ptr<StaticTile>> HillGenerator::generate(sf::Vector2i pointOnGrid, sf::Uint8 size) {
    Log::out("Generating bush");
    std::vector<std::shared_ptr<StaticTile>> tiles;

    sf::Uint32 lineStartPosX = pointOnGrid.x;
    sf::Uint32 filledWidth = size * 2 - 1;

    for (sf::Uint32 i=0; i < size; i++) {
        auto beginLine = tileFactory->createStaticTile(0, 1, grid);
        beginLine->snapToGrid(pointOnGrid);
        pointOnGrid.x++;
        tiles.push_back(beginLine);

        for (sf::Uint32 j=0; j < filledWidth; j++) {
            auto middleLine = tileFactory->createStaticTile(3, 1, grid);
            bool lastTwoLines = size < 3 || i > size-3;
            bool firstOrLastInLine = j == 0 || j == filledWidth-1;

            if (lastTwoLines && firstOrLastInLine) {
                middleLine = tileFactory->createStaticTile(1, 1, grid);
            }
            middleLine->snapToGrid(pointOnGrid);
            pointOnGrid.x++;
            tiles.push_back(middleLine);
        }
        filledWidth-=2;

        auto endLine = tileFactory->createStaticTile(2, 1, grid);
        endLine->snapToGrid(pointOnGrid);
        pointOnGrid.y--;
        lineStartPosX++;
        pointOnGrid.x = lineStartPosX;
        tiles.push_back(endLine);
    }

    pointOnGrid.x = lineStartPosX;
    auto top = tileFactory->createStaticTile(1, 0, grid);
    top->snapToGrid(pointOnGrid);
    tiles.push_back(top);

    return tiles;
}
