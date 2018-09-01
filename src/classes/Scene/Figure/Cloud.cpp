#include "Cloud.hpp"

Cloud::Cloud(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size) : Figure (tileFactory, grid, position) {
    this->size = size;

    if (size < 2) {
        size = 2;
    }

    auto beginTop = tileFactory->createStaticTile(0, 7);
    beginTop->setGrid(grid);
    beginTop->snapToGrid(sf::Vector2u(position));
    position.y--;
    tiles.push_back(beginTop);

    auto beginBottom = tileFactory->createStaticTile(0, 8);
    beginBottom->setGrid(grid);
    beginBottom->snapToGrid(sf::Vector2u(position));
    position.x++;
    position.y++;
    tiles.push_back(beginBottom);

    for (int i=2; i<size; i++) {
        auto middleTop = tileFactory->createStaticTile(1, 7);
        middleTop->setGrid(grid);
        middleTop->snapToGrid(sf::Vector2u(position));
        position.y--;
        tiles.push_back(middleTop);

        auto middleBottom = tileFactory->createStaticTile(1, 8);
        middleBottom->setGrid(grid);
        middleBottom->snapToGrid(sf::Vector2u(position));
        position.x++;
        position.y++;
        tiles.push_back(middleBottom);
    }

    auto endTop = tileFactory->createStaticTile(2, 7);
    endTop->setGrid(grid);
    endTop->snapToGrid(sf::Vector2u(position));
    position.y--;
    tiles.push_back(endTop);

    auto endBottom = tileFactory->createStaticTile(2, 8);
    endBottom->setGrid(grid);
    endBottom->snapToGrid(sf::Vector2u(position));
    tiles.push_back(endBottom);
}
