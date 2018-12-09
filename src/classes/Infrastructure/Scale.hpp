#pragma once

#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/TileConfig.hpp"

class Scale {

public:

    Scale(sf::Vector2u windowSize);

    void change(sf::Vector2u windowSize);

    float getCurrent() const;
    float getRatio() const;
    sf::Vector2u getWindowSize() const;

private:

    TileConfig config;
    sf::Vector2u windowSize;
    float original = 0;
    float current;
    float ratio;

};