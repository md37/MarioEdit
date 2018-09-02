#pragma once

#include <SFML/System/Vector2.hpp>

class Scale {

public:

    Scale();

    void rescale(sf::Vector2u windowSize);

    float getScale();
    float getScaleRatio();

private:

    float scale;
    float scaleRatio;

};