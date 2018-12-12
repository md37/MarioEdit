#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>

class Circle {

public:

    Circle(sf::Vector2f position, sf::Uint32 radius);

    sf::Vector2f getPosition() const;
    sf::Uint32 getRadius() const;

private:

    sf::Vector2f position;
    sf::Uint32 radius;

};
