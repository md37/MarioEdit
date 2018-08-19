#include "UndoHightlightTileAnimation.hpp"

#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>
#include "classes/EasingFunction/LinearFunction.hpp"
#include "classes/EasingFunction/QuadraticFunction.hpp"
#include "classes/EasingFunction/LogarithmFunction.hpp"


class Tile {

public:

    float scalePromotion;
    void snapToGrid();
    void rescaleToWindowBound();
};

UndoHightlightTileAnimation::UndoHightlightTileAnimation(Tile *tile) {
    this->tile = tile;
    this->sleepTime = 10;
    this->duration = 300;
}

void UndoHightlightTileAnimation::run() {
    isRunningFlag = true;

    sf::Clock clock;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    sf::Int32 duration = this->duration;
    sf::Int32 sleepTime = this->sleepTime;
    Tile* tile = this->tile;

    std::thread interval([=]() mutable {
        sf::Int32 animationPointInTime = 0;
        float finishScalePromotion = 0.9f;

        sf::Int32 duration1 = duration/3*2;
        LogarithmFunction function(duration1, tile->scalePromotion, finishScalePromotion);


        do {
            if (isStopped) {
                break;
            }
            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            animationPointInTime = currentMilliseconds-startMilliseconds;
            if (animationPointInTime > duration1) {
                animationPointInTime = duration1;
            }

            tile->scalePromotion = function.getValue(animationPointInTime);
            tile->snapToGrid();
            tile->rescaleToWindowBound();

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } while (animationPointInTime < duration1 || isStopped);


        startMilliseconds = clock.getElapsedTime().asMilliseconds();
        finishScalePromotion = 1.0f;

        sf::Int32 duration2 = duration/3;
        QuadraticFunction function2(duration2, tile->scalePromotion, finishScalePromotion);
        do {
            if (isStopped) {
                break;
            }

            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            animationPointInTime = currentMilliseconds-startMilliseconds;
            if (animationPointInTime > duration2) {
                animationPointInTime = duration2;
            }

            tile->scalePromotion = function2.getValue(animationPointInTime);
            tile->snapToGrid();
            tile->rescaleToWindowBound();

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        } while (animationPointInTime < duration2 || isStopped);

        isRunningFlag = false;
        isStopped = false;
    });
    interval.detach();
}
