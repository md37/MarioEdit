#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Grid {

public:

    explicit Grid(sf::Vector2u windowSize);
    void rescale(sf::Vector2u windowSize);
    bool hasIncompleteEnding();

    sf::Vector2u getSize();
    sf::Vector2f getPointOnGrid(sf::Vector2f pointOnScreen);
    sf::Vector2f pointOnGridToPosition(sf::Vector2u pointOnGrid);
    sf::Vector2f getCenter(sf::Vector2u pointOnGrid);

    void turnHighlightOn();
    void turnHighlightOff();
    void setHighlightPosition(sf::Vector2f cursorPosition);
    sf::Vector2f getHighlightPosition();
    sf::Vector2u getHighlightPlace();

    void draw(std::shared_ptr<sf::RenderWindow> window);

private:

    sf::Vector2u windowSize;
    sf::Uint32 rows = 12;
    sf::Uint32 cols;
    float lineDistance;
    bool hasIncompleteEndingFlag = false;
    
    sf::Uint32 lineThickness;
    sf::Uint32 lineThicknessDivider = 400;
    
    sf::Color lineColor;
    
    bool highlightFlag = false;
    sf::Vector2f highlightPosition;

    void drawHorizontalLine(sf::Uint32 number, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window);
    void drawVerticalLine(sf::Uint32 number, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window);
    void drawHighlight(std::shared_ptr<sf::RenderWindow> window);
};