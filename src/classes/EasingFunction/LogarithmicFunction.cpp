#include "LogarithmicFunction.hpp"

#include <cmath>

LogarithmicFunction::LogarithmicFunction(sf::Int32 duration, float startValue, float targetValue) : EasingFunction(duration, startValue, targetValue) {

}

float LogarithmicFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    if (timePart < infinityBound) {
        timePart = infinityBound;
    }

    float value = (log(timePart)+yOffset);
    float maxValue = (log(1)+yOffset);

    float valuePercent = value/maxValue;
    value = valuePercent*(targetValue-startValue);
    value += startValue;
    return value;
}
