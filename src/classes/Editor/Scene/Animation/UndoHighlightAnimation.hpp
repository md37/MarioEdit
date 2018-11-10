#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/Infrastructure/Animation/EasingFunction.hpp"
#include "classes/Infrastructure/Animation/Animation.hpp"
#include "classes/Infrastructure/Animation/EasingFunction/SmoothStepFunction.hpp"

class DynamicTile;

class UndoHighlightAnimation : public Animation {

public:

    explicit UndoHighlightAnimation(DynamicTile* tile);
    void animate() override;

private:

    DynamicTile* tile;
    std::unique_ptr<SmoothStepFunction> downFunction;
    std::unique_ptr<SmoothStepFunction> upFunction;

};
