#include "SpecialBlockBlinkAnimation.hpp"

#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

SpecialBlockBlinkAnimation::SpecialBlockBlinkAnimation() : Animation(1000, true) {

}

void SpecialBlockBlinkAnimation::animate() {
    auto animationPointInTime = getAnimationPointInTime();

    auto tiles = ObjectRegistry::getDynamicTiles();
    for (auto &tile : tiles) {
        if (!tile->isDragging() && tile->isBlinking) {
            if (animationPointInTime > 900) {
                tile->changeImage(1, 11);
            } else if (animationPointInTime > 800) {
                tile->changeImage(2, 11);
            } else if (animationPointInTime > 700) {
                tile->changeImage(1, 11);
            } else if (animationPointInTime <= 700) {
                tile->changeImage(0, 11);
            }
        }
    }

    if (animationPointInTime >= duration) {
        startMilliseconds = clock.getElapsedTime().asMilliseconds();
    }
}
