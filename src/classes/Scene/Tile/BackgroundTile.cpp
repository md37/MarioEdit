#include "BackgroundTile.hpp"

void BackgroundTile::draw(std::shared_ptr<sf::RenderWindow> window) {
    sprite.setColor(sf::Color(255, 255, 255, transparency));
    window->draw(sprite);
}

void BackgroundTile::setTransparency(sf::Uint8 transparency) {
    this->transparency = transparency;
}