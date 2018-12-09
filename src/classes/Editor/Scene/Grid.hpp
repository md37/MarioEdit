#pragma once

#include <memory>
#include <optional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Scene/Highlight.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"

class Grid : public RescalableInterface, public DrawableInterface {

public:

    void rescale(std::unique_ptr<Scale>& scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    sf::Uint32 getCols();

    sf::Vector2u getSize();
    sf::Vector2f getPointOnGrid(sf::Vector2f pointOnScreen);
    sf::Vector2f pointOnGridToPosition(sf::Vector2i pointOnGrid);
    sf::Vector2i positionToPointOnGrid(sf::Vector2f pointOnScreen);
    sf::Vector2f getCenter(sf::Vector2u pointOnGrid);

    void turnHighlightOn(sf::Vector2u size);
    void turnHighlightOff();
    bool hasIncompleteEnding();

    std::optional<Highlight>& getHighlight();

private:

    sf::Uint32 rows = 12;
    sf::Uint32 cols;
    float lineDistance;
    bool hasIncompleteEndingFlag = false;

    sf::Color lineColor = sf::Color(0, 0, 0, 50);
    sf::Uint32 lineThickness;
    sf::Uint32 lineThicknessDivider = 400;

    std::optional<Highlight> highlight;

    void drawHorizontalLine(sf::Uint32 number, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window);
    void drawVerticalLine(sf::Uint32 number, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window);
};
