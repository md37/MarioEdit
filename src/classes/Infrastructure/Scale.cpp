#include "Scale.hpp"

#include <vector>
#include "classes/Editor/Object/AbstractTile.hpp"
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

float Scale::getCurrent() const {
    return current;
}

float Scale::getRatio() const {
    return ratio;
}

sf::Vector2u Scale::getWindowSize() const {
    return windowSize;
}
