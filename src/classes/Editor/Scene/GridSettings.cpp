#include "GridSettings.hpp"

#include <iostream>

const sf::Uint32 GridSettings::Auto;

GridSettings::GridSettings(sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f size): rows(rows), cols(cols), size(size) {
    rowsOrig = rows;
    colsOrig = cols;
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
    resolveAutoSize(scale);

    size *= scale->getRatio();
    auto size = this->size;

    lineThickness = size.y / lineThicknessDivider;

    if (colsOrig == Auto) {
        lineDistance = size.y / rows;
        cols = sf::Uint32(size.x / lineDistance);
        hasIncompleteEndingFlag = size.x > cols*lineDistance;
    } else {
        lineDistance = size.x / cols;
        rows = sf::Uint32(size.y / lineDistance);
        hasIncompleteEndingFlag = size.y > rows*lineDistance;
    }
}

void GridSettings::resolveAutoSize(const std::unique_ptr<Scale> &scale) {
    if (scale->getRatio() != 1) {
        return;
    }

    auto windowSize = scale->getWindowSize();
    if (size.x == Auto) {
        size.x = windowSize.x;
    }
    if (size.y == Auto) {
        size.y = windowSize.y;
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
