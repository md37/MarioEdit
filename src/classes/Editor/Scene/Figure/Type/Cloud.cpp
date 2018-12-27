#include "Cloud.hpp"

#include <SFML/Graphics/Rect.hpp>
#include "classes/Infrastructure/Log.hpp"

Cloud::Cloud(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size) : DynamicFigure(tileFactory)
{
    if (size < 1) {
        size = 1;
    }

    this->size = size;
    this->grid = std::move(grid);
    generate();
}

Cloud::Cloud(std::unique_ptr<TileFactory> &tileFactory, sf::Uint8 size) : DynamicFigure(tileFactory) {
    if (size < 1) {
        size = 1;
    }

    this->size = size;

    Settings gridSettings(2, 1+size, sf::Vector2f(160+size*80, 160), sf::Vector2f(0, 0));
    grid = std::make_unique<Grid>(gridSettings);

    generate();
}

void Cloud::generate() {
    auto pointOnGrid = this->pointOnGrid;

    auto beginBottom = tileFactory->createStaticTile(0, 8, grid);
    beginBottom->snapToGrid(pointOnGrid);
    pointOnGrid.y--;
    tiles.push_back(beginBottom);

    auto beginTop = tileFactory->createStaticTile(0, 7, grid);
    beginTop->snapToGrid(pointOnGrid);
    pointOnGrid.x++;
    pointOnGrid.y++;
    tiles.push_back(beginTop);

    for (int i=0; i<size; i++) {
        auto middleBottom = tileFactory->createStaticTile(1, 8, grid);
        middleBottom->snapToGrid(pointOnGrid);
        pointOnGrid.y--;
        tiles.push_back(middleBottom);

        auto middleTop = tileFactory->createStaticTile(1, 7, grid);
        middleTop->snapToGrid(pointOnGrid);
        pointOnGrid.x++;
        pointOnGrid.y++;
        tiles.push_back(middleTop);
    }

    auto endBottom = tileFactory->createStaticTile(2, 8, grid);
    endBottom->snapToGrid(pointOnGrid);
    pointOnGrid.y--;
    tiles.push_back(endBottom);

    auto endTop = tileFactory->createStaticTile(2, 7, grid);
    endTop->snapToGrid(pointOnGrid);
    tiles.push_back(endTop);
}

void Cloud::changeVariant(sf::Uint8 variant) {
    if (variant < 1 || variant > 2 || variant == size) {
        return;
    }

    Log::out("Change Figure Variant");

    size = variant;
    tiles.clear();

    std::optional<Highlight>& highlight = grid->getHighlight();
    if (highlight.has_value()) {
        pointOnGrid = highlight->getPointOnGrid();
        pointOnGrid.y++;
        position = highlight->getPosition();

        generate();

        grid->turnHighlightOn(getSizeOnGrid());
        resetFrame();
    }
}
