#pragma once

#include "classes/Animation/EasingFunction.hpp"

class QuadraticFunction : public EasingFunction {

public:

    QuadraticFunction(sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) override;

};
