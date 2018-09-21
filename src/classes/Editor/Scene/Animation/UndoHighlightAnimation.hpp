#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/System/Animation/EasingFunction.hpp"
#include "classes/System/Animation/SmoothAnimation.hpp"

class DynamicTile;

class UndoHighlightAnimation : public SmoothAnimation {

public:

    explicit UndoHighlightAnimation(DynamicTile* tile);
    void run() override;

private:

    DynamicTile* tile;
    sf::Clock clock;
    std::thread thread;
    std::mutex mutex;

    void animate(sf::Int32 duration, EasingFunction& function);

};
