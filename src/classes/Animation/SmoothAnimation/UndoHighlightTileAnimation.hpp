#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include "classes/Animation/SmoothAnimation.hpp"

class DynamicTile;

class UndoHighlightTileAnimation : public SmoothAnimation {

public:

    UndoHighlightTileAnimation(DynamicTile* tile);
    void run() override;

private:

    DynamicTile* tile;
    std::thread thread;
    std::mutex mutex;

};
