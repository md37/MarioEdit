#include "Tilebar.hpp"

#include <SFML/Graphics/Text.hpp>

Tilebar::Tilebar(std::shared_ptr<sf::RenderWindow> window) {
    rescale(window->getSize());
    generateBox(window);
}

void Tilebar::rescale(sf::Vector2u windowSize) {
    boxHeight = windowSize.y*0.155;

    sf::Vector2f size(windowSize);
    size.y = boxHeight;
    box.setSize(size);

    float lineThickness = windowSize.y / lineThicknessDivider;
    box.setOutlineThickness(lineThickness);
}

void Tilebar::generateBox(std::shared_ptr<sf::RenderWindow> window) {
    auto newPosition = box.getPosition();
    box.setPosition(newPosition);

    sf::Color bgColor(188, 211, 254);
    box.setFillColor(bgColor);

    sf::Color borderColor(0, 0, 0);
    box.setOutlineColor(borderColor);
}

void Tilebar::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(box);
    drawDynamicTiles(window);
}

void Tilebar::drawDynamicTiles(std::shared_ptr<sf::RenderWindow> &window) const {

}
