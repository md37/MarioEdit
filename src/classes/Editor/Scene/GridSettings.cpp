#include "GridSettings.hpp"

const sf::Uint32 GridSettings::Auto;

GridSettings::GridSettings(sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f size) {
    this->rows = rows;
    this->cols = cols;
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
    lineDistance = windowSize.y / rows;
    cols = sf::Uint32(windowSize.x / lineDistance);
    hasIncompleteEndingFlag = windowSize.x > cols*lineDistance;
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
