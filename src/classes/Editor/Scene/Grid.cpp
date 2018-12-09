#include "Grid.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

void Grid::rescale(std::unique_ptr<Scale>& scale) {
    auto windowSize = scale->getWindowSize();

    lineThickness = windowSize.y / lineThicknessDivider;
    lineDistance = windowSize.y / rows;
    cols = sf::Uint32(windowSize.x / lineDistance);
    hasIncompleteEndingFlag = windowSize.x > cols*lineDistance;

    if (highlight.has_value()) {
        highlight->setLineDistance(lineDistance);
    }
}

sf::Vector2u Grid::getSize() const {
    return {cols, rows};
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> window) const {
    for (int i=0; i<rows+1; i++) {
        for (int j=0; j<cols+1; j++) {
            drawHorizontalLine(i, j, window);
            drawVerticalLine(i, j, window);
        }
    }

    if (highlight.has_value()) {
        highlight->draw(window);
    }
}

void Grid::drawHorizontalLine(sf::Uint32 row, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) const {
    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(col*lineDistance+((float)lineThickness/2), row*lineDistance-((float)lineThickness/2)));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineDistance-lineThickness, lineThickness));

    window->draw(line);
}

void Grid::drawVerticalLine(sf::Uint32 row, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) const {
    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(col*lineDistance-((float)lineThickness/2), row*lineDistance));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineThickness, lineDistance));

    window->draw(line);
}

sf::Uint32 Grid::getCols() const {
    return cols;
}

bool Grid::hasIncompleteEnding() const {
    return hasIncompleteEndingFlag;
}

void Grid::turnHighlightOn(sf::Vector2u size) {
    highlight.emplace(Highlight(lineColor, lineDistance));
    highlight->setSize(size);
}

void Grid::turnHighlightOff() {
    highlight.reset();
}

std::optional<Highlight>& Grid::getHighlight() {
    return highlight;
}

sf::Vector2i Grid::positionToPointOnGrid(sf::Vector2f pointOnScreen) const {
    sf::Vector2i retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance));
    retval.y = ((int)(pointOnScreen.y/lineDistance));
    return retval;
}

sf::Vector2f Grid::getCenter(sf::Vector2u pointOnGrid) const {
    sf::Vector2f retval(pointOnGrid);
    retval.y = retval.y;
    retval *= lineDistance;
    retval.x += lineDistance/2;
    retval.y -= lineDistance/2;
    return retval;
}

sf::Vector2f Grid::getPointOnGrid(sf::Vector2f pointOnScreen) const {
    sf::Vector2f retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance))*lineDistance;
    retval.y = ((int)(pointOnScreen.y/lineDistance))*lineDistance;
    return retval;
}

sf::Vector2f Grid::pointOnGridToPosition(sf::Vector2i pointOnGrid) const {
    sf::Vector2f retval = sf::Vector2f(pointOnGrid) * lineDistance;
    return retval;
}
