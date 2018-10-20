#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <SFML/System/Clock.hpp>
#include "classes/System/Animation/EasingFunction.hpp"
#include "classes/System/Animation/Animation.hpp"
#include "classes/System/Animation/EasingFunction/SmoothStepFunction.hpp"

class DynamicTile;

class UndoHighlightAnimation : public Animation {

public:

    explicit UndoHighlightAnimation(DynamicTile* tile);
    void animate() override;

private:

    DynamicTile* tile;
    std::shared_ptr<SmoothStepFunction> downFunction;
    std::shared_ptr<SmoothStepFunction> upFunction;

};
