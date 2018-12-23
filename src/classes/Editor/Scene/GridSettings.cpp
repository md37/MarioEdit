#include "GridSettings.hpp"

const sf::Uint32 GridSettings::Auto;

GridSettings::GridSettings(sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f size) {
    this->rows = rows;
    rowsOrig = rows;
    this->cols = cols;
    colsOrig = cols;
    this->size = size;
}

sf::Uint32 GridSettings::getRows() const {
    return rows;
}

sf::Uint32 GridSettings::getCols() const {
    return cols;
}

sf::Vector2f GridSettings::getSize() const {
    return size;
}

void GridSettings::rescale(std::unique_ptr <Scale> &scale) {
    auto windowSize = scale->getWindowSize();
    lineThickness = windowSize.y / lineThicknessDivider;

    if (colsOrig == Auto) {
        lineDistance = windowSize.y / rows;
        cols = sf::Uint32(windowSize.x / lineDistance);
        hasIncompleteEndingFlag = windowSize.x > cols*lineDistance;
    } else {
        lineDistance = windowSize.x / cols;
        rows = sf::Uint32(windowSize.y / lineDistance);
        hasIncompleteEndingFlag = windowSize.y > rows*lineDistance;
    }
}

sf::Uint32 GridSettings::getLineThickness() const {
    return lineThickness;
}

float GridSettings::getLineDistance() const {
    return lineDistance;
}

bool GridSettings::hasIncompleteEnding() const {
    return hasIncompleteEndingFlag;
}
