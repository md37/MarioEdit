#include "SmoothStepFunction.hpp"

SmoothStepFunction::SmoothStepFunction(sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {

}

float SmoothStepFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float valueDiff = targetValue-startValue;
    float smoothStep = smoothstep(0.0f, 1.0f, timePart);
    return valueDiff*smoothStep + startValue;
}

float SmoothStepFunction::smoothstep(float edge0, float edge1, float x) {
    x = clamp((x - edge0) / (edge1 - edge0), edge0, edge1);
    return x * x * (3 - 2 * x);
}

float SmoothStepFunction::clamp(float x, float lowerLimit, float upperLimit) {
    if (x < lowerLimit) {
        x = lowerLimit;
    }
    if (x > upperLimit) {
        x = upperLimit;
    }
    return x;
}
