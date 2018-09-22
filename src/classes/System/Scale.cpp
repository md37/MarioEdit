#include "Scale.hpp"

#include <vector>
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

Scale::Scale() {
    scale = 1.0f;
    scaleRatio = 1.0f;
}

void Scale::rescale(sf::Vector2u windowSize) {
    TileConfig config;
    scale = (float)windowSize.y / (float)(config.tileHeight*config.blocksOnHeight);
    if (originalScale == 0) {
        originalScale = scale;
    }

    scaleRatio = scale/originalScale;
}

float Scale::getScale() {
    return scale;
}

float Scale::getScaleRatio() {
    return scaleRatio;
}
