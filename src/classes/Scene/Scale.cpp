#include "Scale.hpp"

#include <vector>
#include "classes/Scene/Tile.hpp"
#include "classes/Scene/Tile/SceneRegistry.hpp"

Scale::Scale() {
    scale = 1.0f;
    scaleRatio = 1.0f;
}

void Scale::rescale(sf::Vector2u windowSize) {
    TileConfig config;
    float prevScale = scale;
    scale = (float)windowSize.y / (float)(config.tileHeight*config.blocksOnHeight);

    if (prevScale == scale || prevScale == 1.0f) {
        return;
    }

    scaleRatio = scale/prevScale;
}

float Scale::getScale() {
    return scale;
}

float Scale::getScaleRatio() {
    return scaleRatio;
}
