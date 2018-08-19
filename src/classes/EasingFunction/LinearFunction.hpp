#pragma once

#include "classes/EasingFunction.hpp"

class LinearFunction : public EasingFunction {

public:

    LinearFunction(sf::Int32 duration, float minValue, float maxValue);
    virtual float getValue(sf::Int32 time) override;

};
