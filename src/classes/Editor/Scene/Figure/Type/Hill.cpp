#include "Hill.hpp"

#include "classes/Infrastructure/Log.hpp"

Hill::Hill(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : DynamicFigure(tileFactory) {
    if (size < 1) {
        size = 1;
    }
    this->grid = grid;
    this->size = size;

    generate();
}

Hill::Hill(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size): DynamicFigure(tileFactory) {
    if (size < 1) {
        size = 1;
    }
    this->size = size;

    Settings gridSettings(1+size, 2+size, sf::Vector2f(160+size*80, 80+size*80), sf::Vector2f(0, 0));
    grid = std::make_unique<Grid>(gridSettings);

    generate();
}

void Hill::generate() {
    auto pointOnGrid = this->pointOnGrid;

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
}

void Hill::changeVariant(sf::Uint8 variant) {
    if (variant < 1 || variant > 2 || variant == size) {
        return;
    }

    Log::out("Change Figure Variant");

    size = variant;
    tiles.clear();

    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        pointOnGrid = highlight->getPointOnGrid();
        pointOnGrid.y += variant;
        position = highlight->getPosition();

        generate();

        grid->turnHighlightOn(getSizeOnGrid());
        resetFrame();
    }
}
