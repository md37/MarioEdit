#include "UndoHighlightButtonAnimation.hpp"

#include <functional>
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/System/Animation/EasingFunction/SmoothStepFunction.hpp"

UndoHighlightButtonAnimation::UndoHighlightButtonAnimation(ButtonTile *tile) {
    this->tile = tile;
    this->sleepTime = 20;
    this->duration = 300;
}

void UndoHighlightButtonAnimation::run() {
    isRunningFlag = true;

    thread = std::thread([=]() mutable {
        SmoothStepFunction function(duration, tile->scalePromotion, 1.0f);
        animate(duration, function);

        isRunningFlag = false;
        isStopped = false;
    });
    thread.detach();
}

void UndoHighlightButtonAnimation::animate(sf::Int32 duration, EasingFunction& function) {
    sf::Int32 animationPointInTime = 0;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    do {
        mutex.lock();

        if (isStopped) {
            mutex.unlock();
            break;
        }
        sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
        animationPointInTime = currentMilliseconds-startMilliseconds;
        if (animationPointInTime > duration) {
            animationPointInTime = duration;
        }

        tile->scalePromotion = function.getValue(animationPointInTime);
//        tile->snapToGrid();
//        tile->snapToWindowBound();

        mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    } while (animationPointInTime < duration || isStopped);
}
