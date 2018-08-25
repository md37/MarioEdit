#include "Grid.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Grid::Grid(sf::Vector2u windowSize) : lineColor(74, 119, 203, 255) {
    this->rescale(windowSize);
}

void Grid::rescale(sf::Vector2u windowSize) {
    this->windowSize = windowSize;

    lineThickness = windowSize.y / lineThicknessDivider;
    lineDistance = windowSize.y / rows;
    cols = sf::Uint32(windowSize.x / lineDistance);
    hasIncompleteEndingFlag = windowSize.x > cols*lineDistance;
}

sf::Vector2u Grid::getSize() {
    return sf::Vector2u(cols, rows);
}

sf::Vector2f Grid::getPointOnGrid(sf::Vector2f pointOnScreen) {
    sf::Vector2f retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance))*lineDistance;
    retval.y = ((int)(pointOnScreen.y/lineDistance))*lineDistance;
    return retval;
}

sf::Vector2f Grid::pointOnGridToPosition(sf::Vector2u pointOnGrid) {
    sf::Vector2f retval = sf::Vector2f(pointOnGrid) * lineDistance;
    retval.y = lineDistance*(rows-1) - retval.y;
    return retval;
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i=0; i<rows+1; i++) {
        drawHorizontalLine(i, window);
    }

    for (int i=1; i<cols+1; i++) {
        drawVerticalLine(i, window);
    }

    if (highlightFlag) {
        drawHighlight(window);
    }
}

void Grid::drawHorizontalLine(sf::Uint32 number, std::shared_ptr<sf::RenderWindow> window) {
    sf::Uint32 posY = number*lineDistance;

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(0, posY-lineThickness/2));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(windowSize.x, lineThickness));

    window->draw(line);
}

void Grid::drawVerticalLine(sf::Uint32 number, std::shared_ptr<sf::RenderWindow> window) {
    sf::Uint32 posX = number*lineDistance;

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(posX-lineThickness/2, 0));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineThickness, windowSize.y));

    window->draw(line);
}

void Grid::drawHighlight(std::shared_ptr<sf::RenderWindow> window) {
    sf::RectangleShape line;
    line.setPosition(highlightPosition);
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineDistance, lineDistance));

    window->draw(line);
}

sf::Vector2f Grid::getHighlightPosition() {
    return highlightPosition;
}

void Grid::setHighlightPosition(sf::Vector2f cursorPosition) {
    highlightPosition = getPointOnGrid(cursorPosition);
}

sf::Vector2f Grid::getCenter(sf::Vector2u pointOnGrid) {
    sf::Vector2f retval(pointOnGrid);
    retval.y = rows-retval.y;
    retval *= lineDistance;
    retval.x += lineDistance/2;
    retval.y -= lineDistance/2;
    return retval;
}

sf::Vector2u Grid::getHighlightPlace() {
    sf::Vector2u retval(highlightPosition/lineDistance);
    retval.y = rows-retval.y-1;
    return retval;
}

void Grid::turnHighlightOn() {
    highlightFlag = true;
}

void Grid::turnHighlightOff() {
    highlightFlag = false;
}

bool Grid::hasIncompleteEnding() {
    return hasIncompleteEndingFlag;
}
