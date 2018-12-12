#pragma once

#include "classes/Infrastructure/Animation/EasingFunction.hpp"

class BiasFunction : public EasingFunction {

public:

    BiasFunction(float deviation, sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) const override;

private:

    float deviation;

};
