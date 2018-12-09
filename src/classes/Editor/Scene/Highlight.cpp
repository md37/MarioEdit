#include "Highlight.hpp"

Highlight::Highlight(sf::Color color, float lineDistance) : lineDistance(lineDistance) {
    area.setFillColor(color);
}

void Highlight::draw(std::shared_ptr<sf::RenderWindow> window) {
    area.setPosition(position);
    area.setSize(sf::Vector2f(lineDistance*size.x, lineDistance*size.y));
    window->draw(area);
}

void Highlight::setPosition(sf::Vector2f position) {
    position.x = ((int)(position.x/lineDistance))*lineDistance;
    position.y = ((int)(position.y/lineDistance))*lineDistance;

    this->position = position;
}

sf::Vector2f Highlight::getPosition() {
    return position;
}

void Highlight::setSize(sf::Vector2u size) {
    this->size = size;
}

sf::Vector2u Highlight::getSize() {
    return size;
}

sf::Vector2i Highlight::getPointOnGrid() {
    return sf::Vector2i(position/lineDistance);
}

sf::Vector2u Highlight::getSizeOnGrid() {
    return sf::Vector2u();
}

void Highlight::setLineDistance(float lineDistance) {
    this->lineDistance = lineDistance;
}
