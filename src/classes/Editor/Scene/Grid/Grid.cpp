#include "Grid.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/Infrastructure/Log.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

Grid::Grid(Settings settings): settings(settings) {

}

void Grid::rescale(std::unique_ptr<Scale>& scale) {
    Log::out("Rescaling grid");

    settings.rescale(scale);

    if (highlight.has_value()) {
        highlight->setLineDistance(settings.getLineDistance());
    }
}

sf::Vector2u Grid::getSize() const {
    return {settings.getCols(), settings.getRows()};
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> window) const {
    for (int i=0; i<settings.getRows()+1; i++) {
        for (int j=0; j<settings.getCols()+1; j++) {
            drawHorizontalLine(i, j, window);
            drawVerticalLine(i, j, window);
        }
    }

    if (highlight.has_value()) {
        highlight->draw(window);
    }
}

void Grid::drawHorizontalLine(sf::Uint32 row, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) const {
    auto lineDistance = settings.getLineDistance();
    auto lineThickness = settings.getLineThickness();

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(col*lineDistance+((float)lineThickness/2), row*lineDistance-((float)lineThickness/2)));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineDistance-lineThickness, lineThickness));

    window->draw(line);
}

void Grid::drawVerticalLine(sf::Uint32 row, sf::Uint32 col, std::shared_ptr<sf::RenderWindow> window) const {
    auto lineDistance = settings.getLineDistance();
    auto lineThickness = settings.getLineThickness();

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(col*lineDistance-((float)lineThickness/2), row*lineDistance));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(lineThickness, lineDistance));

    window->draw(line);
}

sf::Uint32 Grid::getCols() const {
    return settings.getCols();
}

bool Grid::hasIncompleteEnding() const {
    return settings.hasIncompleteEnding();
}

void Grid::turnHighlightOn(sf::Vector2u size) {
    highlight.emplace(Highlight(lineColor, settings.getLineDistance()));
    highlight->setSize(size);
}

void Grid::turnHighlightOff() {
    highlight.reset();
}

std::optional<Highlight>& Grid::getHighlight() {
    return highlight;
}

sf::Vector2i Grid::positionToPointOnGrid(sf::Vector2f pointOnScreen) const {
    auto lineDistance = settings.getLineDistance();
    pointOnScreen -= settings.getPosition();

    sf::Vector2i retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance));
    retval.y = ((int)(pointOnScreen.y/lineDistance));
    return retval;
}

sf::Vector2f Grid::getCenter(sf::Vector2u pointOnGrid) const {
    auto lineDistance = settings.getLineDistance();

    sf::Vector2f retval(pointOnGrid);
    retval *= lineDistance;
    retval.x += lineDistance/2;
    retval.y -= lineDistance/2;
    retval += settings.getPosition();
    return retval;
}

sf::Vector2f Grid::getPointOnGrid(sf::Vector2f pointOnScreen) const {
    sf::Uint32 lineDistance = settings.getLineDistance();

    sf::Vector2f retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/lineDistance))*lineDistance;
    retval.y = ((int)(pointOnScreen.y/lineDistance))*lineDistance;
    return retval;
}

sf::Vector2f Grid::pointOnGridToPosition(sf::Vector2i pointOnGrid) const {
    sf::Vector2f retval = settings.getPosition() + sf::Vector2f(pointOnGrid) * settings.getLineDistance();
    return retval;
}
