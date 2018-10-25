#include "Hill.hpp"

Hill::Hill(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size) : Figure(tileFactory, grid, position) {
    if (size < 1) {
        size = 1;
    }
    this->size = size;

    sf::Uint32 lineStartPosX = position.x;
    sf::Uint32 filledWidth = size*2-1;

    for (sf::Uint32 i=0; i<size; i++) {
        auto beginLine = tileFactory->createStaticTile(0, 1);
        beginLine->setGrid(grid);
        beginLine->snapToGrid(sf::Vector2i(position));
        position.x++;
        tiles.push_back(beginLine);

        for (sf::Uint32 j=0; j<filledWidth; j++) {
            auto middleLine = tileFactory->createStaticTile(3, 1);
            bool lastTwoLines = size < 3 || i > size-3;
            bool firstOrLastInLine = j == 0 || j == filledWidth-1;

            if (lastTwoLines && firstOrLastInLine) {
                middleLine = tileFactory->createStaticTile(1, 1);
            }
            middleLine->setGrid(grid);
            middleLine->snapToGrid(sf::Vector2i(position));
            position.x++;
            tiles.push_back(middleLine);
        }
        filledWidth-=2;

        auto endLine = tileFactory->createStaticTile(2, 1);
        endLine->setGrid(grid);
        endLine->snapToGrid(sf::Vector2i(position));
        position.y--;
        lineStartPosX++;
        position.x = lineStartPosX;
        tiles.push_back(endLine);
    }

    position.x = lineStartPosX;
    auto top = tileFactory->createStaticTile(1, 0);
    top->setGrid(grid);
    top->snapToGrid(sf::Vector2i(position));
    tiles.push_back(top);
}
