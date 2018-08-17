#include "QuadraticFunction.hpp"

#include <cmath>

QuadraticFunction::QuadraticFunction(sf::Int32 a, sf::Int32 b, sf::Int32 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

float QuadraticFunction::getValue(sf::Int32 time) {
    float value = a*time*time + b*time + c;
    value *= abs(minValue)+abs(maxValue);
    value += minValue;
    return value;
}
