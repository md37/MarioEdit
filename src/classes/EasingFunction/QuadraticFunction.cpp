#include "QuadraticFunction.hpp"

#include <cmath>

QuadraticFunction::QuadraticFunction(sf::Int32 a, sf::Int32 b, sf::Int32 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

float QuadraticFunction::getValue(sf::Int32 time) {
    float timePart = (float)time/(float)duration;
    float value = a*timePart*timePart + b*timePart + c;
    value *= maxValue-minValue;
    value += minValue;
    return value;
}
