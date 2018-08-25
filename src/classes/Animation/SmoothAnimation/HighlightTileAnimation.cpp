#include "HighlightTileAnimation.hpp"

#include <iostream>
#include <functional>
#include "classes/Tile/DynamicTile.hpp"
#include "classes/EasingFunction/LinearFunction.hpp"
#include "classes/EasingFunction/QuadraticFunction.hpp"
#include "classes/EasingFunction/LogarithmicFunction.hpp"

HighlightTileAnimation::HighlightTileAnimation(DynamicTile* tile) {
    this->tile = tile;
    this->sleepTime = 10;
    this->duration = 300;
}

void HighlightTileAnimation::run() {
    isRunningFlag = true;

    thread = std::thread([=]() mutable {
        sf::Int32 duration1 = duration/3*2;
        LogarithmicFunction function1(duration1, tile->scalePromotion, 1.8f);
        animate(duration1, function1);

        sf::Int32 duration2 = duration/3;
        LogarithmicFunction function2(duration2, tile->scalePromotion, 1.5f);
        animate(duration2, function2);

        isRunningFlag = false;
        isStopped = false;
    });
    thread.detach();
}

void HighlightTileAnimation::animate(sf::Int32 duration, EasingFunction& function) {
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
        tile->snapToCenterPoint();
        tile->correctCorners();
        mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    } while (animationPointInTime < duration || isStopped);
}