#include "Scale.hpp"

#include <vector>
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

Scale::Scale(sf::Vector2u windowSize) {
    change(windowSize);
    original = current;
    ratio = 1.0f;
}

void Scale::change(sf::Vector2u windowSize) {
    this->windowSize = windowSize;
    current = (float)windowSize.y / (float)(config.tileHeight*config.blocksOnHeight);
    ratio = current/original;
    original = current;
}

float Scale::getCurrent() {
    return current;
}

float Scale::getRatio() {
    return ratio;
}

sf::Vector2u Scale::getWindowSize() {
    return windowSize;
}
