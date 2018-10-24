#include "Grid.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

Grid::Grid() : lineColor(0, 0, 0, 50) {

}

void Grid::rescale(std::shared_ptr<Scale> scale) {
    auto windowSize = scale->getWindowSize();

    lineThickness = windowSize.y / lineThicknessDivider;
    lineDistance = windowSize.y / rows;
    cols = sf::Uint32(windowSize.x / lineDistance);
    hasIncompleteEndingFlag = windowSize.x > cols*lineDistance;
}

sf::Vector2u Grid::getSize() {
    return {cols, rows};
}

sf::Vector2f Grid::getPointOnGrid(sf::Vector2f pointOnScreen) {
    sf::Vector2f retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance))*lineDistance;
    retval.y = ((int)(pointOnScreen.y/lineDistance))*lineDistance;
    return retval;
}

sf::Vector2f Grid::pointOnGridToPosition(sf::Vector2u pointOnGrid) {
    sf::Vector2f retval = sf::Vector2f(pointOnGrid) * lineDistance;
    return retval;
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i=0; i<rows+1; i++) {
        for (int j=0; j<cols+1; j++) {
            drawHorizontalLine(i, j, window);
            drawVerticalLine(i, j, window);
        }
    }

    if (highlightFlag) {
        drawHighlight(window);
    }
}

void Grid::drawHorizontalLine(sf::Uint32 row, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) {
    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(col*lineDistance+((float)lineThickness/2), row*lineDistance-((float)lineThickness/2)));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineDistance-lineThickness, lineThickness));

    window->draw(line);
}

void Grid::drawVerticalLine(sf::Uint32 row, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) {
    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(col*lineDistance-((float)lineThickness/2), row*lineDistance));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineThickness, lineDistance));

    window->draw(line);
}

void Grid::drawHighlight(std::shared_ptr<sf::RenderWindow> window) {
    sf::RectangleShape line;
    line.setPosition(highlightPosition);
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineDistance, lineDistance));

    window->draw(line);
}

sf::Uint32 Grid::getCols() {
    return cols;
}

sf::Vector2f Grid::getHighlightPosition() {
    return highlightPosition;
}

void Grid::setHighlightPosition(sf::Vector2f cursorPosition) {
    highlightPosition = getPointOnGrid(cursorPosition);
}

sf::Vector2f Grid::getCenter(sf::Vector2u pointOnGrid) {
    sf::Vector2f retval(pointOnGrid);
    retval.y = retval.y;
    retval *= lineDistance;
    retval.x += lineDistance/2;
    retval.y -= lineDistance/2;
    return retval;
}

sf::Vector2u Grid::getHighlightPlace() {
    sf::Vector2u retval(highlightPosition/lineDistance);
    return retval;
}

bool Grid::hasIncompleteEnding() {
    return hasIncompleteEndingFlag;
}

void Grid::turnHighlightOn() {
    highlightFlag = true;
}

void Grid::turnHighlightOff() {
    highlightFlag = false;
}

sf::Vector2u Grid::positionToGridPlace(sf::Vector2f pointOnScreen) {
    sf::Vector2u retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance));
    retval.y = ((int)(pointOnScreen.y/lineDistance));
    return retval;
}

sf::Uint32 Grid::getLineThickness() {
    return lineThickness;
}
