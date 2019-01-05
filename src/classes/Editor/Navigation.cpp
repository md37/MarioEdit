#include "Navigation.hpp"

Navigation::Navigation(std::unique_ptr<TileFactory> &tileFactory) : tileFactory(tileFactory) {
    tileNavigation = std::make_unique<TileNavigation>(tileFactory);
    figureNavigation = std::make_unique<FigureNavigation>(tileFactory);
}

void Navigation::draw(std::shared_ptr<sf::RenderWindow> window) const {
    tileNavigation->draw(window);
    figureNavigation->draw(window);
}

void Navigation::rescale(std::unique_ptr<Scale> &scale) {
    tileNavigation->rescale(scale);
    figureNavigation->rescale(scale);
}
