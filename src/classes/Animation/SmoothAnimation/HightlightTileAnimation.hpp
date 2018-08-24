#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include "classes/Animation/SmoothAnimation.hpp"

class Tile;

class HightlightTileAnimation : public SmoothAnimation {

public:

    HightlightTileAnimation(Tile* tile);
    void run() override;

private:

    Tile* tile;
    std::thread thread;
    std::mutex mutex;

};
