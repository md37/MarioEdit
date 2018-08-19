#pragma once

#include <memory>
#include <functional>
#include "classes/Animation/SmoothAnimation.hpp"

class Tile;

class HighlightTileAnimation : public SmoothAnimation {

public:

    HighlightTileAnimation(Tile* tile);
    void run() override;

private:

    Tile* tile;

};
