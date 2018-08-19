#include "LinearFunction.hpp"

LinearFunction::LinearFunction(sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {

}

float LinearFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = timePart;
    value *= targetValue-startValue;
    value += startValue;
    return value;
}
