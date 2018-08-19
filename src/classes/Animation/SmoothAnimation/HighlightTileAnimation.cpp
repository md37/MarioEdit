#include "HighlightTileAnimation.hpp"

#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>
#include "classes/EasingFunction/LinearFunction.hpp"
#include "classes/EasingFunction/QuadraticFunction.hpp"
#include "classes/EasingFunction/JellyFunction.hpp"

class Tile {

public:

    float scalePromotion;

    void rescaleCenter();
    void correctCorners();
};

HighlightTileAnimation::HighlightTileAnimation(Tile* tile) {
    this->tile = tile;
    this->sleepTime = 10;
    this->duration = 300;
}

void HighlightTileAnimation::run() {
    sf::Clock clock;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    sf::Int32 duration = this->duration;
    sf::Int32 sleepTime = this->sleepTime;
    Tile* tile = this->tile;

    std::thread interval([=]() {
        sf::Int32 animationPointInTime = 0;

        JellyFunction function(duration, tile->scalePromotion, tile->scalePromotion*1.5f);

        while (animationPointInTime < duration) {
            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            animationPointInTime = currentMilliseconds-startMilliseconds;

            tile->scalePromotion = function.getValue(animationPointInTime);
            tile->rescaleCenter();
            tile->correctCorners();

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    });
    interval.detach();
}
