#include "QuadraticFunction.hpp"

#include <cmath>

QuadraticFunction::QuadraticFunction(sf::Int32 duration, float minValue, float maxValue) : EasingFunction(duration, minValue, maxValue) {

}

float QuadraticFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = timePart*timePart;
    value *= targetValue-startValue;
    value += startValue;
    return value;
}
