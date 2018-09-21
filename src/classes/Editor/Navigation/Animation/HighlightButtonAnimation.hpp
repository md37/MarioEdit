#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/System/Animation/EasingFunction.hpp"
#include "classes/System/Animation/SmoothAnimation.hpp"

class ButtonTile;

class HighlightButtonAnimation : public SmoothAnimation {

public:

    explicit HighlightButtonAnimation(ButtonTile* tile);
    void run() override;

private:

    ButtonTile* tile;
    sf::Clock clock;
    std::thread thread;
    std::mutex mutex;

    void animate(sf::Int32 duration, EasingFunction& function);
};
