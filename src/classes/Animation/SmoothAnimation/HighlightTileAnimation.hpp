#pragma once

#include <memory>
#include <functional>
#include "classes/Animation/SmoothAnimation.hpp"

class HighlightTileAnimation : public SmoothAnimation {

public:

    HighlightTileAnimation(float* tileScalePromotion);
    void run() override;

private:

    float* tileScalePromotion;

};
