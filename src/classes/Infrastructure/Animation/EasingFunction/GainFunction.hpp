#pragma once

#include "classes/Infrastructure/Animation/EasingFunction.hpp"

class GainFunction : public EasingFunction {

public:

    GainFunction(float deviation, sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) override;

private:

    float deviation;

    float bias(float deviation, float timePart);

};
