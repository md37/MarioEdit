#pragma once

#include "classes/Editor/Scene/ResizeIndicator.hpp"
#include "classes/Editor/Scene/Figure.hpp"

class Cloud : public Figure {

public:

    Cloud(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> grid, sf::Uint8 size);

    void draw(std::shared_ptr<sf::RenderWindow> window) override;
    void snapToGrid(sf::Vector2i pointOnGrid) override;
    void rescale(std::unique_ptr<Scale> &scale) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

protected:

    void generate(std::unique_ptr<TileFactory> &tileFactory, std::shared_ptr<Grid> &grid, sf::Uint8 size);

private:

    sf::Uint8 size;

    std::unique_ptr<ResizeIndicator> leftIndicator;
    std::unique_ptr<ResizeIndicator> rightIndicator;

    void reCreateIndicators();
    void resizeToLeft();
    void resizeToRight();
};
