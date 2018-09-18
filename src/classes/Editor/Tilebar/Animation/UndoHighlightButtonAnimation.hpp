#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/Animation/EasingFunction.hpp"
#include "classes/Animation/SmoothAnimation.hpp"

class ButtonTile;

class UndoHighlightButtonAnimation : public SmoothAnimation {

public:

    explicit UndoHighlightButtonAnimation(ButtonTile* tile);
    void run() override;

private:

    ButtonTile* tile;
    sf::Clock clock;
    std::thread thread;
    std::mutex mutex;

    void animate(sf::Int32 duration, EasingFunction& function);

};
