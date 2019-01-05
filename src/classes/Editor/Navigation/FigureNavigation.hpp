#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Editor/Object/StaticFigure.hpp"
#include "classes/Editor/Navigation/AbstractNavigation.hpp"
#include "classes/Editor/Navigation/FigureButton.hpp"
#include "classes/Infrastructure/Scale.hpp"

class FigureNavigation : AbstractNavigation {

public:

    explicit FigureNavigation(std::unique_ptr<TileFactory> &tileFactory);
    void rescale(std::unique_ptr<Scale>& scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

private:

    std::unique_ptr<TileFactory> &tileFactory;

    sf::RectangleShape box;
    sf::Uint32 boxWidth = 530;
    sf::Uint32 boxHeight = 120;
    sf::Vector2f boxPosition = {428.0f, 0.0f};

    std::vector<std::shared_ptr<FigureButton>> buttons;

    void generateBox();
    void generateButtons();

};
