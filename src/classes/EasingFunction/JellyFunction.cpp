#include "JellyFunction.hpp"

#include <cmath>

JellyFunction::JellyFunction(sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {

}

float JellyFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    if (timePart < infinityBound) {
        timePart = infinityBound;
    }
    if (timePart <= breakPoint) {
        return risingFunction(timePart);
    }
    return fallingFunction(timePart);
}

float JellyFunction::risingFunction(float timePart) {
    float value = (log(timePart)+yOffset) * scaleUp;
    float maxValue = (log(breakPoint)+yOffset);

    float valuePercent = value/maxValue;
    value = valuePercent*(targetValue-startValue);
    value += startValue;
    return value;
}

float JellyFunction::fallingFunction(float timePart) {
    float magicalConst = scaleUp;
    float maxRisingValue = risingFunction(breakPoint);
    float x = timePart*magicalConst-breakPoint;
    float value = -(x*x)+maxRisingValue;
    return value;
}
