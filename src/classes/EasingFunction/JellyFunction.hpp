#pragma once

#include "classes/EasingFunction.hpp"

class JellyFunction : public EasingFunction {

public:

    JellyFunction(sf::Int32 duration, float minValue, float maxValue);
    virtual float getValue(sf::Int32 time) override;

private:

    sf::Int32 yOffset = 3;
    float infinityBound = 0.05f;
    float scaleUp = 1.2f;
    float breakPoint = 0.75f;

    float risingFunction(float timePart);
    float fallingFunction(float timePart);

};
