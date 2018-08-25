#include "HighlightTileAnimation.hpp"

#include <iostream>
#include <functional>
#include <SFML/System/Clock.hpp>
#include "classes/EasingFunction/LinearFunction.hpp"
#include "classes/EasingFunction/QuadraticFunction.hpp"
#include "classes/EasingFunction/LogarithmicFunction.hpp"

class Tile {

public:

    float scalePromotion;

    void snapToCenterPoint();
    void correctCorners();
};

HighlightTileAnimation::HighlightTileAnimation(Tile* tile) {
    this->tile = tile;
    this->sleepTime = 10;
    this->duration = 300;
}

void HighlightTileAnimation::run() {
    isRunningFlag = true;

    sf::Clock clock;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    sf::Int32 duration = this->duration;
    sf::Int32 sleepTime = this->sleepTime;
    Tile* tile = this->tile;

    thread = std::thread([=]() mutable {
        sf::Int32 animationPointInTime = 0;

        float finishScalePromotion = 1.8f;
        sf::Int32 duration1 = duration/3*2;
        LogarithmicFunction function(duration1, tile->scalePromotion, finishScalePromotion);

        do {
            mutex.lock();
            if (isStopped) {
                mutex.unlock();
                break;
            }

            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            animationPointInTime = currentMilliseconds-startMilliseconds;
            if (animationPointInTime > duration1) {
                animationPointInTime = duration1;
            }

            tile->scalePromotion = function.getValue(animationPointInTime);
            tile->snapToCenterPoint();
            tile->correctCorners();
            mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } while (animationPointInTime < duration1 || isStopped);

        finishScalePromotion = 1.5f;
        startMilliseconds = clock.getElapsedTime().asMilliseconds();

        sf::Int32 duration2 = duration/3;
        LogarithmicFunction function2(duration2, tile->scalePromotion, finishScalePromotion);

        do {
            mutex.lock();
            if (isStopped) {
                mutex.unlock();
                break;
            }

            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            animationPointInTime = currentMilliseconds-startMilliseconds;
            if (animationPointInTime > duration2) {
                animationPointInTime = duration2;
            }

            tile->scalePromotion = function2.getValue(animationPointInTime);
            tile->snapToCenterPoint();
            tile->correctCorners();
            mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } while (animationPointInTime < duration2 || isStopped);

        isRunningFlag = false;
        isStopped = false;
    });
    thread.detach();
}