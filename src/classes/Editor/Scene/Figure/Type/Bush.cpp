#include "Bush.hpp"

#include "classes/Infrastructure/Log.hpp"

Bush::Bush(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : DynamicFigure(tileFactory), generator(tileFactory, grid, size) {
    if (size < 1) {
        size = 1;
    }

    this->grid = grid;
    this->size = size;

    tiles = generator.generate(pointOnGrid);
}

Bush::Bush(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size): DynamicFigure(tileFactory), generator(tileFactory, grid, size) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    Settings gridSettings(1, 1+size, sf::Vector2f(160+size*80, 80), sf::Vector2f(0, 0));
    grid = std::make_unique<Grid>(gridSettings);

    generator.updateGrid(grid);
    tiles = generator.generate(pointOnGrid);
}

void Bush::changeVariant(sf::Uint8 variant) {
    if (variant < 1 || variant > 2 || variant == size) {
        return;
    }

    Log::out("Change Figure Variant");

    size = variant;
    tiles.clear();

    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        pointOnGrid = highlight->getPointOnGrid();
        position = highlight->getPosition();

        tiles = generator.generate(pointOnGrid);

        grid->turnHighlightOn(getSizeOnGrid());
        resetFrame();
    }
}
