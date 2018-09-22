#pragma once

#include <SFML/System/Vector2.hpp>
#include "classes/System/Interface/RescalableInterface.hpp"

class Scale : public RescalableInterface {

public:

    Scale();

    void rescale(sf::Vector2u windowSize) override;

    float getScale();
    float getScaleRatio();

private:

    float scale;
    float scaleRatio;
    float originalScale = 0;

};