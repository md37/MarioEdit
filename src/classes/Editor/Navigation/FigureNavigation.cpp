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
        sf::Vector2f position = boxPosition + sf::Vector2f(-15.0f, 12.0f);
        sf::Vector2i pointOnGrid = {0, 1};
        Settings gridSettings(0.8, position);
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
        std::shared_ptr<CloudGenerator> generator = std::make_shared<CloudGenerator>(tileFactory, grid);
        std::shared_ptr<FigureButton> button = std::make_shared<FigureButton>(
            position, tileFactory, grid, generator, pointOnGrid
        );
        button->cutBorder(-4, 24, 28, 28);
        button->variantPositionChange = 1;
        buttons.push_back(button);
        ObjectRegistry::add(button);
    }

    {
        sf::Vector2f position = boxPosition + sf::Vector2f(135.0f, 44.0f);
        Settings gridSettings(0.8, position);
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
        std::shared_ptr<BushGenerator> generator = std::make_shared<BushGenerator>(tileFactory, grid);
        std::shared_ptr<FigureButton> button = std::make_shared<FigureButton>(
            position, tileFactory, grid, generator
        );
        button->cutBorder(-36, 24, -4, 28);
        button->variantPositionChange = 0;
        buttons.push_back(button);
        ObjectRegistry::add(button);
    }

    {
        sf::Vector2f position = boxPosition + sf::Vector2f(310.0f, -20.0f);
        sf::Vector2i pointOnGrid = {0, 1};
        Settings gridSettings(0.8, position);
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(gridSettings);
        std::shared_ptr<HillGenerator> generator = std::make_shared<HillGenerator>(tileFactory, grid);
        std::shared_ptr<FigureButton> button = std::make_shared<FigureButton>(
            position, tileFactory, grid, generator, pointOnGrid
        );
        button->cutBorder(28, -4, -4, -3);
        button->variantPositionChange = DynamicFigure::VariantAutoChange;
        buttons.push_back(button);
        ObjectRegistry::add(button);
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
