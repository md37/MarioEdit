#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/EasingFunction/LogarithmicFunction.hpp"
#include "classes/Animation/SmoothAnimation.hpp"

class DynamicTile;

class HighlightTileAnimation : public SmoothAnimation {

public:

    HighlightTileAnimation(DynamicTile* tile);
    void run() override;

private:

    DynamicTile* tile;
    sf::Clock clock;
    std::thread thread;
    std::mutex mutex;

    void animate(sf::Int32 duration, LogarithmicFunction &function);
};
