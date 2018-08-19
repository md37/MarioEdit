#pragma once

#include "classes/EasingFunction.hpp"

class QuadraticFunction : public EasingFunction {

public:

    QuadraticFunction(sf::Int32 duration, float minValue, float maxValue);
    virtual float getValue(sf::Int32 time) override;

};
