#pragma once

#include <SFML/Config.hpp>

class EasingFunction {

public:

    void setDuration(sf::Int32 duration);
    void setMinValue(float value);
    void setMaxValue(float value);

    virtual float getValue(sf::Int32 time)=0;

protected:

    sf::Int32 duration = 1000;
    float minValue = 0.0f;
    float maxValue = 1.0f;

};