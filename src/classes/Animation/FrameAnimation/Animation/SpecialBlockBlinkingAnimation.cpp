#include "SpecialBlockBlinkingAnimation.hpp"

#include "classes/Tile/DynamicTile.hpp"
#include "classes/Tile/TileRegistry.hpp"
#include "classes/Animation/FrameAnimation/Frame.hpp"

SpecialBlockBlinkingAnimation::SpecialBlockBlinkingAnimation() {
    duration = 1000;

    addFrame(std::make_shared<Frame>(0, 70, [=]() {
        auto tiles = TileRegistry::getDynamicTiles();
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->changeImage(0, 5);
            }
        }
    }));

    addFrame(std::make_shared<Frame>(70, 80, [=]() {
        auto tiles = TileRegistry::getDynamicTiles();
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->changeImage(1, 5);
            }
        }
    }));

    addFrame(std::make_shared<Frame>(80, 90, [=]() {
        auto tiles = TileRegistry::getDynamicTiles();
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->changeImage(2, 5);
            }
        }
    }));

    addFrame(std::make_shared<Frame>(90, 100, [=]() {
        auto tiles = TileRegistry::getDynamicTiles();
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->changeImage(1, 5);
            }
        }
    }));
}