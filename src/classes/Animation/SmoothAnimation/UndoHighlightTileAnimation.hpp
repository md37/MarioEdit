#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include "classes/Animation/SmoothAnimation.hpp"

class Tile;

class UndoHighlightTileAnimation : public SmoothAnimation {

public:

    UndoHighlightTileAnimation(Tile* tile);
    void run() override;

private:

    Tile* tile;
    std::thread thread;
    std::mutex mutex;

};
