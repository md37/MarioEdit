#pragma once

#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/TileConfig.hpp"

class Scale {

public:

    Scale(sf::Vector2u windowSize);

    void change(sf::Vector2u windowSize);

    float getCurrent();
    float getRatio();
    sf::Vector2u getWindowSize();

private:

    TileConfig config;
    sf::Vector2u windowSize;
    float original = 0;
    float current;
    float ratio;

};