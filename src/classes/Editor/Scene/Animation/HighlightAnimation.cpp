#include "HighlightAnimation.hpp"

#include <functional>
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Infrastructure/Animation/EasingFunction/SmoothStepFunction.hpp"

HighlightAnimation::HighlightAnimation(DynamicTile* tile) : Animation(600, false) {
    this->tile = tile;

    upFunction = std::make_unique<SmoothStepFunction>(200, tile->getScalePromotion(), 1.8f);
    downFunction = std::make_unique<SmoothStepFunction>(100, 1.8f, 1.5f);
}

void HighlightAnimation::animate() {
    auto animationPointInTime = getAnimationPointInTime();

    if (animationPointInTime < 200) {
        auto newScalePromotion = upFunction->getValue(animationPointInTime);
        tile->setScalePromotion(newScalePromotion);
    } else {
        auto newScalePromotion = downFunction->getValue(animationPointInTime-200);
        tile->setScalePromotion(newScalePromotion);
    }

    tile->snapToCenterPoint();
    tile->correctCorners();
}