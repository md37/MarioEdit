#include "FigureNavigation.hpp"

#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Object/FigureGenerator/CloudGenerator.hpp"
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
    Settings gridSettings(2, 3, sf::Vector2f(100, 100), sf::Vector2f(300, 200));
    std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
    BushGenerator bushGenerator(tileFactory, grid, 1);
    std::shared_ptr<FigureButton> bushButton = std::make_shared<FigureButton>(tileFactory, grid, bushGenerator);
    buttons.push_back(bushButton);
}

void FigureNavigation::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(box);

    for (auto &button: buttons) {
        button->draw(window);
    }
}

void FigureNavigation::rescale(std::unique_ptr<Scale> &scale) {
    auto boxSize = box.getSize();
    if (boxSize.x == 0) {
        boxSize = sf::Vector2f(boxWidth, boxHeight);
    }
    boxSize *= scale->getRatio();
    box.setSize(boxSize);
    box.setPosition(scale->getRatio()*box.getPosition());

    for (auto &button: buttons) {
        button->rescale(scale);
    }
}
