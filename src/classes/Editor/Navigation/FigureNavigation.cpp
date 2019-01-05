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
    {
        sf::Vector2f position = boxPosition + sf::Vector2f(-15.0f, 75.0f);
        Settings gridSettings(0.8, position);
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
        std::shared_ptr<CloudGenerator> generator = std::make_shared<CloudGenerator>(tileFactory, grid, 1);
        std::shared_ptr<FigureButton> button = std::make_shared<FigureButton>(
            position, tileFactory, grid, generator
        );
        button->cutBorder(-67, 23, 92, 28);
        buttons.push_back(button);
    }

    {
        sf::Vector2f position = boxPosition + sf::Vector2f(135.0f, 48.0f);
        Settings gridSettings(0.8, position);
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
        std::shared_ptr<BushGenerator> generator = std::make_shared<BushGenerator>(tileFactory, grid, 1);
        std::shared_ptr<FigureButton> button = std::make_shared<FigureButton>(
            position, tileFactory, grid, generator
        );
        button->cutBorder(-40, 22, 1, 27);
        buttons.push_back(button);
    }

    {
        sf::Vector2f position = boxPosition + sf::Vector2f(308.0f, 48.0f);
        Settings gridSettings(0.8, position);
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
        std::shared_ptr<HillGenerator> generator = std::make_shared<HillGenerator>(tileFactory, grid, 1);
        std::shared_ptr<FigureButton> button = std::make_shared<FigureButton>(
            position, tileFactory, grid, generator
        );
        button->cutBorder(-40, 0, 65, 0);
        buttons.push_back(button);
    }
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
