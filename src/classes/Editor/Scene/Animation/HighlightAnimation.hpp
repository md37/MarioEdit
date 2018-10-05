#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include <classes/System/Animation/EasingFunction/SmoothStepFunction.hpp>
#include "classes/System/Animation/EasingFunction.hpp"
#include "classes/System/Animation/Animation.hpp"

class DynamicTile;

class HighlightAnimation : public Animation {

public:

    explicit HighlightAnimation(DynamicTile* tile);
    void animate() override;

private:

    DynamicTile* tile;
    std::shared_ptr<SmoothStepFunction> upFunction;
    std::shared_ptr<SmoothStepFunction> downFunction;
};
