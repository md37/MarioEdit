#include "BushGenerator.hpp"

#include "classes/Infrastructure/Log.hpp"

BushGenerator::BushGenerator(
        std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size
) : AbstractFigureGenerator(tileFactory, grid, size) {

}

std::vector<std::shared_ptr<StaticTile>> BushGenerator::generate(sf::Vector2i pointOnGrid) {
    Log::out("Generating bush");

    std::vector<std::shared_ptr<StaticTile>> tiles;

    auto begin = tileFactory->createStaticTile(2, 0, grid);
    begin->snapToGrid(pointOnGrid);
    pointOnGrid.x++;
    tiles.push_back(begin);

    for (int i=0; i<size; i++) {
        auto middle = tileFactory->createStaticTile(3, 0, grid);
        middle->snapToGrid(pointOnGrid);
        pointOnGrid.x++;
        tiles.push_back(middle);
    }

    auto end = tileFactory->createStaticTile(4, 0, grid);
    end->snapToGrid(pointOnGrid);
    tiles.push_back(end);

    return tiles;
}
