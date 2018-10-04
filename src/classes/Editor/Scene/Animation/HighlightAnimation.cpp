#include "HighlightAnimation.hpp"

#include <functional>
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/System/Animation/EasingFunction/SmoothStepFunction.hpp"

HighlightAnimation::HighlightAnimation(DynamicTile* tile) : Animation(600, false) {
    this->tile = tile;

    upFunction = std::make_shared<SmoothStepFunction>(200, tile->scalePromotion, 1.8f);
    downFunction = std::make_shared<SmoothStepFunction>(100, 1.8f, 1.5f);
}

void HighlightAnimation::animate() {
    auto animationPointInTime = getAnimationPointInTime();

    if (animationPointInTime < 200) {
        tile->scalePromotion = upFunction->getValue(animationPointInTime);
    } else {
        tile->scalePromotion = downFunction->getValue(animationPointInTime-200);
    }

    tile->snapToCenterPoint();
    tile->correctCorners();
}