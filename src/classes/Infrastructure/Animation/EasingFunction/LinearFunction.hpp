#pragma once

#include "classes/Infrastructure/Animation/EasingFunction.hpp"

class LinearFunction : public EasingFunction {

public:

    LinearFunction(sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) const override;

};
