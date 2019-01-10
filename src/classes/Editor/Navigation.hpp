#pragma once

#include "classes/Editor/Navigation/TileNavigation.hpp"
#include "classes/Editor/Navigation/FigureNavigation.hpp"

class Navigation : DrawableInterface, RescalableInterface {

public:

    explicit Navigation(std::unique_ptr<TileFactory> &tileFactory);

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;
    void rescale(std::unique_ptr<Scale> &scale) override;

private:

    std::unique_ptr<TileFactory> &tileFactory;

    std::unique_ptr<TileNavigation> tileNavigation;
    std::unique_ptr<FigureNavigation> figureNavigation;

};
