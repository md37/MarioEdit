#pragma once

#include <SFML/Config.hpp>

class EasingFunction {

public:

    EasingFunction(sf::Int32 duration, float startValue, float targetValue);

    virtual float getValue(sf::Int32 time) const=0;

protected:

    sf::Int32 duration = 1000;

    float startValue = 0.0f;
    float targetValue = 1.0f;

};