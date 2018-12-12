#include "BackgroundTile.hpp"

void BackgroundTile::draw(std::shared_ptr<sf::RenderWindow> window) const {
    window->draw(sprite);
}

void BackgroundTile::setTransparency(sf::Uint8 transparency) {
    this->transparency = transparency;
    sprite.setColor(sf::Color(255, 255, 255, transparency));
}