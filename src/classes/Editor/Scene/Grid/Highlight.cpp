#include "Highlight.hpp"

#include <iostream>

Highlight::Highlight(sf::Color color, float lineDistance) : lineDistance(lineDistance) {
    area.setFillColor(color);
    recalculateSize();
}

void Highlight::recalculateSize() {
    area.setSize(sf::Vector2f(lineDistance * size.x, lineDistance * size.y));
}

void Highlight::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(area);
}

void Highlight::setPosition(sf::Vector2f position) {
    position.x = ((int)(position.x/lineDistance))*lineDistance;
    position.y = ((int)(position.y/lineDistance))*lineDistance;

    area.setPosition(position);
}

sf::Vector2f Highlight::getPosition() const {
    return area.getPosition();
}

void Highlight::setSize(sf::Vector2u size) {
    this->size = size;
    recalculateSize();
}

sf::Vector2u Highlight::getSize() const {
    return size;
}

sf::Vector2i Highlight::getPointOnGrid() const {
    return sf::Vector2i(getPosition()/lineDistance);
}

sf::Vector2u Highlight::getSizeOnGrid() const {
    return sf::Vector2u();
}

void Highlight::setLineDistance(float lineDistance) {
    this->lineDistance = lineDistance;
    recalculateSize();
}
