#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include "classes/Animation/SmoothAnimation.hpp"

class Tile;

class UndoHightlightTileAnimation : public SmoothAnimation {

public:

    UndoHightlightTileAnimation(Tile* tile);
    void run() override;

private:

    Tile* tile;
    std::thread thread;
    std::mutex mutex;

};
