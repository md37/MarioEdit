#include "Cloud.hpp"

#include <SFML/Graphics/Rect.hpp>
#include "classes/Infrastructure/Log.hpp"

Cloud::Cloud(
    std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size
) : DynamicFigure(tileFactory), generatorObject(tileFactory, grid) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;
    this->grid = grid;

    generator = [=](sf::Vector2i pointOnGrid, sf::Uint32 size) mutable {
        return generatorObject.generate(pointOnGrid, size);
    };
    tiles = generator(pointOnGrid, size);
    variantPositionChange = 1;
}

Cloud::Cloud(
    std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size
) : DynamicFigure(tileFactory), generatorObject(tileFactory, grid) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    Settings gridSettings(2, 1+size, sf::Vector2f(160+size*80, 160), sf::Vector2f(0, 0));
    grid = std::make_unique<Grid>(gridSettings);

    generator = [=](sf::Vector2i pointOnGrid, sf::Uint32 size) mutable {
        return generatorObject.generate(pointOnGrid, size);
    };

    generatorObject.updateGrid(grid);
    tiles = generator(pointOnGrid, size);
    variantPositionChange = 1;
}
