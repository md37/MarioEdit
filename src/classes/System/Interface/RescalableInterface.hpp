#pragma once

#include <SFML/System/Vector2.hpp>

class RescalableInterface {

public:

    virtual void rescale(sf::Vector2u windowSize)=0;

};