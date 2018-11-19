#include "UndoHighlightAnimation.hpp"

#include <functional>
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

UndoHighlightAnimation::UndoHighlightAnimation(DynamicTile *tile) : Animation(300, false) {
    this->tile = tile;

    downFunction = std::make_unique<SmoothStepFunction>(200, tile->getScalePromotion(), 0.9f);
    upFunction = std::make_unique<SmoothStepFunction>(100, 0.9f, 1.0f);

    this->setFinishCallback([=]() mutable {
        tile->isReturning = false;
    });
}

void UndoHighlightAnimation::animate() {
    auto animationPointInTime = getAnimationPointInTime();

    if (animationPointInTime < 200) {
        auto newScalePromotion = downFunction->getValue(animationPointInTime);
        tile->setScalePromotion(newScalePromotion);
    } else {
        auto newScalePromotion = upFunction->getValue(animationPointInTime-200);
        tile->setScalePromotion(newScalePromotion);
    }
    tile->snapToCenterPoint();

    auto dropPlace = tile->getDropHighlightPlace();
    if (!tile->isOnIncompletePoint(dropPlace)) {
        tile->correctCorners();
    }
}
