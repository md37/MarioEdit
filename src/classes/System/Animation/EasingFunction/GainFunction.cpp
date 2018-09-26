#include "GainFunction.hpp"

#include <cmath>

GainFunction::GainFunction(float deviation, sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {
    this->deviation = deviation;
}

float GainFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value;
    if (timePart < 0.5f) {
        value = bias(1-deviation, 2*timePart)/2;
    } else {
        value = 1 - bias(1-deviation, 2 - 2*timePart)/2;
    }
    value *= targetValue-startValue;
    value += startValue;
    return value;
}

float GainFunction::bias(float deviation, float timePart) {
    return pow(timePart, log(deviation)/log(0.5f));
}
