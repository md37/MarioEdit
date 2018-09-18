#include "HighlightButtonAnimation.hpp"

#include <iostream>
#include <functional>
#include "classes/Editor/Tilebar/Tile/ButtonTile.hpp"
#include "classes/Animation/EasingFunction/SmoothStepFunction.hpp"

HighlightButtonAnimation::HighlightButtonAnimation(ButtonTile* tile) {
    this->tile = tile;
    this->sleepTime = 20;
    this->duration = 300;
}

void HighlightButtonAnimation::run() {
    isRunningFlag = true;

    thread = std::thread([=]() mutable {
        SmoothStepFunction function(duration, tile->scalePromotion, 1.5f);
        animate(duration, function);

        isRunningFlag = false;
        isStopped = false;
    });
    thread.detach();
}

void HighlightButtonAnimation::animate(sf::Int32 duration, EasingFunction& function) {
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
//        tile->snapToCenterPoint();
//        tile->correctCorners();
        mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    } while (animationPointInTime < duration || isStopped);
}