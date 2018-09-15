#pragma once

#include "classes/EasingFunction.hpp"

class GammaFunction : public EasingFunction {

public:

    GammaFunction(float deviation, sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) override;

private:

    float deviation = 1.0f;

};
