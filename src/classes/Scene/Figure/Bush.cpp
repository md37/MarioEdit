#include "Bush.hpp"

Bush::Bush(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Grid> grid, sf::Vector2i position, sf::Uint8 size) : Figure(tileFactory, grid, position) {
    this->size = size;

    if (size < 2) {
        size = 2;
    }

    auto begin = tileFactory->createStaticTile(2, 0);
    begin->setGrid(grid);
    begin->snapToGrid(sf::Vector2u(position));
    position.x++;
    tiles.push_back(begin);

    for (int i=2; i<size; i++) {
        auto middle = tileFactory->createStaticTile(3, 0);
        middle->setGrid(grid);
        middle->snapToGrid(sf::Vector2u(position));
        position.x++;
        tiles.push_back(middle);
    }

    auto end = tileFactory->createStaticTile(4, 0);
    end->setGrid(grid);
    end->snapToGrid(sf::Vector2u(position));
    tiles.push_back(end);
}
