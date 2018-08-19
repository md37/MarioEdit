#pragma once

#include "classes/EasingFunction.hpp"

class LinearFunction : public EasingFunction {

public:

    LinearFunction(sf::Int32 duration, float startValue, float targetValue);
    virtual float getValue(sf::Int32 time) override;

};
