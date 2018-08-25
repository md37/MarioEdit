#pragma once

#include "classes/Animation/FrameAnimation.hpp"

class DynamicTile;

class SpecialBlockBlinkingAnimation : public FrameAnimation {

public:

    SpecialBlockBlinkingAnimation(std::vector<std::shared_ptr<DynamicTile>> tiles);

};