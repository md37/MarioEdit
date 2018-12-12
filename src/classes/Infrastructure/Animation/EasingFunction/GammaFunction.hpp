#pragma once

#include "classes/Infrastructure/Animation/EasingFunction.hpp"

class GammaFunction : public EasingFunction {

public:

    GammaFunction(float deviation, sf::Int32 duration, float startValue, float targetValue);
    float getValue(sf::Int32 time) const override;

private:

    float deviation = 1.0f;

};
