#pragma once

#include "classes/Infrastructure/Animation/EasingFunction.hpp"

class SmoothStepFunction : public EasingFunction {

public:

    SmoothStepFunction(sf::Int32 duration, float startValue, float targetValue);

    float getValue(sf::Int32 time) const override;

private:

    float smoothstep(float edge0, float edge1, float x) const;
    float clamp(float x, float lowerLimit, float upperLimit) const;

};
