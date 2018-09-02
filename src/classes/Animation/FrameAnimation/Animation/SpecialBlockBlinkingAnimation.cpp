#include "SpecialBlockBlinkingAnimation.hpp"

#include "classes/Scene/Tile/DynamicTile.hpp"
#include "classes/Scene/SceneRegistry.hpp"
#include "classes/Animation/FrameAnimation/Frame.hpp"

SpecialBlockBlinkingAnimation::SpecialBlockBlinkingAnimation() {
    duration = 1000;

    addFrame(std::make_shared<Frame>(0, 70, [=]() {
        auto tiles = SceneRegistry::getDynamicTiles();
        for (auto tile : tiles) {
            if (!tile->isDragging() && tile->isBlinking) {
                tile->changeImage(0, 11);
            }
        }
    }));

    addFrame(std::make_shared<Frame>(70, 80, [=]() {
        auto tiles = SceneRegistry::getDynamicTiles();
        for (auto tile : tiles) {
            if (!tile->isDragging() && tile->isBlinking) {
                tile->changeImage(1, 11);
            }
        }
    }));

    addFrame(std::make_shared<Frame>(80, 90, [=]() {
        auto tiles = SceneRegistry::getDynamicTiles();
        for (auto tile : tiles) {
            if (!tile->isDragging() && tile->isBlinking) {
                tile->changeImage(2, 11);
            }
        }
    }));

    addFrame(std::make_shared<Frame>(90, 100, [=]() {
        auto tiles = SceneRegistry::getDynamicTiles();
        for (auto tile : tiles) {
            if (!tile->isDragging() && tile->isBlinking) {
                tile->changeImage(1, 11);
            }
        }
    }));
}