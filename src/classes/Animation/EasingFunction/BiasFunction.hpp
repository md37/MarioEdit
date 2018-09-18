#pragma once

#include "classes/Animation/EasingFunction.hpp"

class BiasFunction : public EasingFunction {

public:

    BiasFunction(float deviation, sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) override;

private:

    float deviation;

};
