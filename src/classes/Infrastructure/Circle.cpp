#include "Circle.hpp"

Circle::Circle(sf::Vector2f position, sf::Uint32 radius) {
    this->position = position;
    this->radius = radius;
}

sf::Vector2f Circle::getPosition() {
    return position;
}

sf::Uint32 Circle::getRadius() {
    return radius;
}
