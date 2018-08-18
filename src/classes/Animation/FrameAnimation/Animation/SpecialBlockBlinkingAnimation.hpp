#pragma once

#include "classes/Animation/FrameAnimation.hpp"
#include "classes/Tile.hpp"

class SpecialBlockBlinkingAnimation : public FrameAnimation {

public:

    SpecialBlockBlinkingAnimation(std::vector<std::shared_ptr<Tile>> tiles);

};