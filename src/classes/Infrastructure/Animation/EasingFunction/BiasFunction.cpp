#include "BiasFunction.hpp"

#include <cmath>

BiasFunction::BiasFunction(float deviation, sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {
    this->deviation = deviation;
}

float BiasFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = pow(timePart, log(deviation)/log(0.5f));
    value *= targetValue-startValue;
    value += startValue;
    return value;
}
