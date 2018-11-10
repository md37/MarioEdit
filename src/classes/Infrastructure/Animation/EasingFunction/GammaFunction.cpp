#include "GammaFunction.hpp"

#include <cmath>

GammaFunction::GammaFunction(float deviation, sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {
    this->deviation = deviation;
}

float GammaFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = pow(timePart, 1.0f/deviation);
    value *= targetValue-startValue;
    value += startValue;
    return value;
}
