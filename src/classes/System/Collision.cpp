#include "Collision.hpp"

Collision::Collision(sf::Rect<float> first) {
    this->first = first;
}

Collision::Direction Collision::checkCollision(sf::Rect<float> second) {
    auto centerFirst = calcCenter(first);
    auto centerSecond = calcCenter(second);

    auto diff = centerFirst-centerSecond;

    bool isOutsideX = abs((long int)diff.x) > first.width/2 + second.width/2;
    bool isOutsideY = abs((long int)diff.y) > first.height/2 + second.height/2;
    if (isOutsideX || isOutsideY) {
        return Direction::None;
    }

    bool isHorizontalPlacement = abs((long int)diff.x) > abs((long int)diff.y);
    if (isHorizontalPlacement) {
        if (centerFirst.x > centerSecond.x) {
            return Direction::Left;
        }
        return Direction::Right;
    }

    if (centerFirst.y > centerSecond.y) {
        return Direction::Top;
    }
    return Direction::Bottom;
}

sf::Vector2f Collision::calcCenter(sf::Rect<float> rect) {
    return {rect.left + rect.width/2, rect.top + rect.height/2};
}
