#include "QuadraticFunction.hpp"

QuadraticFunction::QuadraticFunction(sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {

}

float QuadraticFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = timePart*timePart;
    value *= targetValue-startValue;
    value += startValue;
    return value;
}
