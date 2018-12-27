#include "Bush.hpp"

#include "classes/Infrastructure/Log.hpp"

Bush::Bush(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : DynamicFigure(tileFactory) {
    if (size < 1) {
        size = 1;
    }

    this->grid = grid;
    this->size = size;
    generate();
}

Bush::Bush(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size): DynamicFigure(tileFactory) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    Settings gridSettings(1, 1+size, sf::Vector2f(160+size*80, 80), sf::Vector2f(0, 0));
    grid = std::make_unique<Grid>(gridSettings);

    generate();
}

void Bush::generate() {
    auto pointOnGrid = this->pointOnGrid;

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
        generate();

        grid->turnHighlightOn(getSizeOnGrid());
        resetFrame();
    }
}
