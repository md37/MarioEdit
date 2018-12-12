#pragma once

#include "classes/Infrastructure/Animation/EasingFunction.hpp"

class LogarithmicFunction : public EasingFunction {

public:

    LogarithmicFunction(sf::Int32 duration, float minValue, float maxValue);
    float getValue(sf::Int32 time) const override;

private:

    sf::Int32 yOffset = 3;
    float infinityBound = 0.05f;

};
