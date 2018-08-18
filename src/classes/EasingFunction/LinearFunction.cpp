#include "LinearFunction.hpp"

#include <cmath>

LinearFunction::LinearFunction(sf::Int32 a, sf::Int32 b) {
    this->a = a;
    this->b = b;
}

float LinearFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = a*timePart + b;
    value *= abs(minValue)+abs(maxValue);
    value += minValue;
    return value;
}
