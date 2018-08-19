#include "EasingFunction.hpp"

EasingFunction::EasingFunction(sf::Int32 duration, float startValue, float targetValue) {
    this->duration = duration;
    this->startValue = startValue;
    this->targetValue = targetValue;
}
