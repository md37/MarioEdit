#pragma once

#include <memory>
#include <functional>
#include "classes/Animation/SmoothAnimation.hpp"

class Tile;

class HightlightTileAnimation : public SmoothAnimation {

public:

    HightlightTileAnimation(Tile* tile);
    void run() override;

private:

    Tile* tile;

};
