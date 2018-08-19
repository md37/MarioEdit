#pragma once

#include <memory>
#include <functional>
#include "classes/Animation/SmoothAnimation.hpp"

class Tile;

class UndoHightlightTileAnimation : public SmoothAnimation {

public:

    UndoHightlightTileAnimation(Tile* tile);
    void run() override;

private:

    Tile* tile;

};
