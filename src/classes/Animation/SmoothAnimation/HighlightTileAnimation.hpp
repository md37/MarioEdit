#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include "classes/Animation/SmoothAnimation.hpp"

class DynamicTile;

class HighlightTileAnimation : public SmoothAnimation {

public:

    HighlightTileAnimation(DynamicTile* tile);
    void run() override;

private:

    DynamicTile* tile;
    std::thread thread;
    std::mutex mutex;

};
