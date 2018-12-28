#include "FigureNavigation.hpp"

#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Infrastructure/Log.hpp"

FigureNavigation::FigureNavigation(std::unique_ptr<TileFactory> &tileFactory): tileFactory(tileFactory) {
    generateBox();
    generateButtons();
}

void FigureNavigation::generateBox() {
    auto newPosition = box.getPosition();
    box.setPosition(newPosition);

    sf::Color bgColor(188, 211, 254);
    box.setFillColor(bgColor);

    sf::Color borderColor(255, 255, 255);
    box.setOutlineColor(borderColor);

    box.setPosition(boxPosition);
}

void FigureNavigation::generateButtons() {
//    auto cloud = std::make_shared<ButtonCloud>(tileFactory, 1);
//    cloud->snapToGrid(sf::Vector2i(0, 0));
//    figures.push_back(cloud);
}

void FigureNavigation::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(box);

    for (auto &figure: figures) {
        figure->draw(window);
    }
}

void FigureNavigation::rescale(std::unique_ptr<Scale> &scale) {
    auto boxSize = box.getSize();
    if (boxSize.x == 0) {
        boxSize = sf::Vector2f(boxWidth, boxHeight);
    }
    boxSize *= scale->getRatio();
    box.setSize(boxSize);
    Log::out(scale->getRatio(), "Ratio");
    box.setPosition(scale->getRatio()*box.getPosition());

    for (auto &figure: figures) {
        figure->rescale(scale);
    }
}
