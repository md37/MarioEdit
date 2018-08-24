#include "Grid.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Grid::Grid(sf::Vector2u windowSize) : lineColor(74, 119, 203, 255) {
    this->rescale(windowSize);
}

void Grid::rescale(sf::Vector2u windowSize) {
    this->windowSize = windowSize;

    lineThickness = windowSize.y / lineThicknessDivider;
    distance = windowSize.y / rows;
    cols = windowSize.x / distance;
}

sf::Vector2u Grid::getSize() {
    return sf::Vector2u(cols, rows);
}

sf::Vector2f Grid::getPointOnGrid(sf::Vector2f pointOnScreen) {
    sf::Vector2f retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/distance))*distance;
    retval.y = ((int)(pointOnScreen.y/distance))*distance;
    return retval;
}

sf::Vector2f Grid::pointOnGridToPosition(sf::Vector2u pointOnGrid) {
    sf::Vector2f retval = sf::Vector2f(pointOnGrid) * distance;
    retval.y = distance*(rows-1) - retval.y;
    return retval;
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i=0; i<rows+1; i++) {
        drawHorizontalLine(i, window);
    }

    for (int i=1; i<cols+1; i++) {
        drawVerticalLine(i, window);
    }

    if (hightlight) {
        drawHightlight(window);
    }
}

void Grid::drawHorizontalLine(sf::Uint32 number, std::shared_ptr<sf::RenderWindow> window) {
    sf::Uint32 posY = number*distance;

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(0, posY-lineThickness/2));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(windowSize.x, lineThickness));

    window->draw(line);
}

void Grid::drawVerticalLine(sf::Uint32 number, std::shared_ptr<sf::RenderWindow> window) {
    sf::Uint32 posX = number*distance;

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(posX-lineThickness/2, 0));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineThickness, windowSize.y));

    window->draw(line);
}

void Grid::drawHightlight(std::shared_ptr<sf::RenderWindow> window) {
    sf::RectangleShape line;
    line.setPosition(highlightPosition);
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(distance, distance));

    window->draw(line);
}

sf::Vector2f Grid::getHighlightPosition() {
    return highlightPosition;
}

sf::Vector2f Grid::getCenter(sf::Vector2u pointOnGrid) {
    sf::Vector2f retval(pointOnGrid);
    retval.y = rows-retval.y;
    retval *= distance;
    retval.x += distance/2;
    retval.y -= distance/2;
    return retval;
}

sf::Vector2u Grid::getHighlightPlace() {
    sf::Vector2u retval(highlightPosition/distance);
    retval.y = rows-retval.y-1;
    return retval;
}

void Grid::hightlightOn() {
    hightlight = true;
}

void Grid::hightlightOff() {
    hightlight = false;
}

void Grid::setHightlightPosition(sf::Vector2f cursorPosition) {
    highlightPosition = getPointOnGrid(cursorPosition);
}
