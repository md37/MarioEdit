#pragma once

#include <SFML/Config.hpp>

class EasingFunction {

public:

    void setMinValue(float value);
    void setMaxValue(float value);

    virtual float getValue(sf::Int32 time)=0;

protected:

    float minValue = 0.0f;
    float maxValue = 1.0f;

};