#include "Settings.hpp"

#include "classes/Infrastructure/Log.hpp"

const sf::Uint32 Settings::Auto;

Settings::Settings(
    sf::Uint32 rows, sf::Uint32 cols, sf::Vector2f position, sf::Vector2f size
): rows(rows), cols(cols), position(position), size(size) {
    rowsOrig = rows;
    colsOrig = cols;
    sizeOrig = size;
}


Settings::Settings(sf::Vector2f position, float scale): scale(scale), position(position) {
    rows = 12;
    cols = Settings::Auto;
    size = sf::Vector2f(Settings::Auto, Settings::Auto);

    rowsOrig = rows;
    colsOrig = cols;
    sizeOrig = size;
}

sf::Uint32 Settings::getRows() const {
    return rows;
}

sf::Uint32 Settings::getCols() const {
    return cols;
}

sf::Vector2f Settings::getSize() const {
    return size;
}

void Settings::rescale(std::unique_ptr<Scale> &scale) {
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

void Settings::resolveAutoSize(const std::unique_ptr<Scale> &scale) {
    auto windowSize = scale->getWindowSize();
    if (sizeOrig.x == Auto) {
        size.x = windowSize.x;
    }
    if (sizeOrig.y == Auto) {
        size.y = windowSize.y;
    }
}

sf::Uint32 Settings::getLineThickness() const {
    return lineThickness;
}

float Settings::getLineDistance() const {
    return lineDistance;
}

bool Settings::hasIncompleteEnding() const {
    return hasIncompleteEndingFlag;
}

sf::Vector2f Settings::getPosition() const {
    return position;
}

float Settings::getScale() const {
    return scale;
}
