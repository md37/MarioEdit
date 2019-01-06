#include "Bush.hpp"

#include "classes/Infrastructure/Log.hpp"

Bush::Bush(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size
) : DynamicFigure(tileFactory), generatorObject(tileFactory, grid) {
    if (size < 1) {
        size = 1;
    }

    this->grid = grid;
    this->size = size;

    generator = [=](sf::Vector2i pointOnGrid, sf::Uint32 size) mutable {
        return generatorObject.generate(pointOnGrid, size);
    };
    tiles = generator(pointOnGrid, size);
    variantPositionChange = 0;
}

Bush::Bush(
    std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size
): DynamicFigure(tileFactory), generatorObject(tileFactory, grid) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    Settings gridSettings(1, 1+size, sf::Vector2f(160+size*80, 80), sf::Vector2f(0, 0));
    grid = std::make_unique<Grid>(gridSettings);

    generator = [=](sf::Vector2i pointOnGrid, sf::Uint32 size) mutable {
        return generatorObject.generate(pointOnGrid, size);
    };

    generatorObject.updateGrid(grid);
    tiles = generator(pointOnGrid, size);
    variantPositionChange = 0;
}