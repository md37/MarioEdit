#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/Infrastructure/Animation/EasingFunction/SmoothStepFunction.hpp"
#include "classes/Infrastructure/Animation/EasingFunction.hpp"
#include "classes/Infrastructure/Animation/Animation.hpp"

class DynamicTile;

class HighlightAnimation : public Animation {

public:

    explicit HighlightAnimation(DynamicTile* tile);
    void animate() override;

private:

    DynamicTile* tile;
    std::unique_ptr<SmoothStepFunction> upFunction;
    std::unique_ptr<SmoothStepFunction> downFunction;
};
