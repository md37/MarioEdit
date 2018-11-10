#pragma once

#include <SFML/Graphics/Rect.hpp>

class Collision {

public:

    enum Direction {
        None=0, Top, Left, Bottom, Right
    };

    explicit Collision(sf::Rect<float> first);

    Direction checkCollision(sf::Rect<float> second);

private:

    sf::Rect<float> first;
    sf::Vector2f calcCenter(sf::Rect<float> rect);
};
