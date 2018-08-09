#include "Scale.hpp"

#include <vector>
#include <iostream>
#include "Tile.hpp"
#include "TileRegistry.hpp"

float Scale::scale = 1.0f;
float Scale::scaleRatio = 1.0f;

const sf::Uint32 Scale::blocksOnHeight = 12;
const sf::Uint32 Scale::blockHeight = 16;

void Scale::reset() {
    scale = 1.0f;
    scaleRatio = 1.0f;
}

void Scale::rescale(sf::Vector2u windowSize) {
    float prevScale = Scale::scale;
    scale = (float)windowSize.y / (float)(blockHeight*blocksOnHeight);

    if (prevScale == Scale::scale || prevScale == 1.0f) {
        return;
    }

    scaleRatio = Scale::scale/prevScale;
}

float Scale::getScale() {
    return Scale::scale;
}

float Scale::getScaleRatio() {
    return Scale::scaleRatio;
}
