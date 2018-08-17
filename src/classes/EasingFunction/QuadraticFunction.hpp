#pragma once

#include "classes/EasingFunction.hpp"

class QuadraticFunction : public EasingFunction {

public:

    QuadraticFunction(sf::Int32 a, sf::Int32 b, sf::Int32 c);

    virtual float getValue(sf::Int32 time) override;

private:

    sf::Int32 a;
    sf::Int32 b;
    sf::Int32 c;

};
