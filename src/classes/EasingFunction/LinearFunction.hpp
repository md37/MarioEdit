#pragma once

#include "classes/EasingFunction.hpp"

class LinearFunction : public EasingFunction {

public:

    LinearFunction(sf::Int32 a, sf::Int32 b);

    virtual float getValue(sf::Int32 time) override;

private:

    sf::Int32 a;
    sf::Int32 b;

};
