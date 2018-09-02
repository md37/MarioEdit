#pragma once

#include "classes/EasingFunction.hpp"

class SmoothStepFunction : public EasingFunction {

public:

    SmoothStepFunction(sf::Int32 duration, float startValue, float targetValue);

    float getValue(sf::Int32 time) override;

private:

    float smoothstep(float edge0, float edge1, float x);
    float clamp(float x, float lowerLimit, float upperLimit);

};
