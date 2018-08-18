#include "HighlightTileAnimation.hpp"

#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>
#include "classes/EasingFunction/LinearFunction.hpp"
#include "classes/EasingFunction/QuadraticFunction.hpp"

HighlightTileAnimation::HighlightTileAnimation(float* tileScalePromotion) {
    this->tileScalePromotion = tileScalePromotion;
    this->sleepTime = 10;
    this->duration = 100;
}

void HighlightTileAnimation::run() {
    sf::Clock clock;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    sf::Int32 duration = this->duration;
    sf::Int32 sleepTime = this->sleepTime;

    std::thread interval([=]() {
        sf::Int32 animationPointInTime = 0;

        LinearFunction function(1, 0);

        function.setMinValue(*tileScalePromotion);
        function.setMaxValue(*tileScalePromotion*2.0f);
        function.setDuration(duration);

        while (animationPointInTime < duration) {
            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            animationPointInTime = currentMilliseconds-startMilliseconds;

            *tileScalePromotion = function.getValue(animationPointInTime);

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    });
    interval.detach();
}
