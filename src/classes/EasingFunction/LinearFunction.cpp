#include "LinearFunction.hpp"

#include <cmath>

LinearFunction::LinearFunction(sf::Int32 duration, float minValue, float maxValue) : EasingFunction(duration, minValue, maxValue) {

}

float LinearFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = timePart;
    value *= targetValue-startValue;
    value += startValue;
    return value;
}
