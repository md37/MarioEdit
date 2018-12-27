#include "GridSettings.hpp"

#include <iostream>

#include <iostream>
#include <classes/Infrastructure/Log.hpp>

const sf::Uint32 GridSettings::Auto;

GridSettings::GridSettings(
    sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f size, sf::Vector2f position
): rows(rows), cols(cols), size(size), position(position) {
    rowsOrig = rows;
    colsOrig = cols;
    sizeOrig = size;
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

void GridSettings::rescale(std::unique_ptr<Scale> &scale) {
    size *= scale->getRatio();

    resolveAutoSize(scale);

    lineThickness = size.y / lineThicknessDivider;
    lineDistance = size.y / rows;

    if (colsOrig == Auto) {
        lineDistance = size.y / rows;
        cols = sf::Uint32(size.x / lineDistance);
        hasIncompleteEndingFlag = size.x > cols*lineDistance;
        Log::out(cols, "Grid cols rescaled");
    } else if (rowsOrig == Auto) {
        lineDistance = size.x / cols;
        rows = sf::Uint32(size.y / lineDistance);
        hasIncompleteEndingFlag = size.y > rows*lineDistance;
        Log::out(rows, "Grid rows rescaled");
    }
}

void GridSettings::resolveAutoSize(const std::unique_ptr<Scale> &scale) {
    auto windowSize = scale->getWindowSize();
    if (sizeOrig.x == Auto) {
        size.x = windowSize.x;
    }
    if (sizeOrig.y == Auto) {
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

sf::Vector2f GridSettings::getPosition() const {
    return position;
}
