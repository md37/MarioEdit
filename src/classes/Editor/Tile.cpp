#include "Tile.hpp"

#include <SFML/Graphics/Texture.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

std::shared_ptr<sf::RenderWindow> Tile::window;

void Tile::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
    Tile::window = window;
}

Tile::Tile(sf::Sprite sprite, TileConfig config) {
    this->sprite = sprite;
    this->config = config;
}

void Tile::changeImage(sf::Uint32 x, sf::Uint32 y) {
    sf::IntRect textureRect;
    textureRect.width = config.tileWidth;
    textureRect.height = config.tileHeight;

    textureRect.top = (y * (config.tileHeight+config.separatorY)) + config.offsetY;
    textureRect.left = (x * (config.tileWidth+config.separatorX)) + config.offsetX;
    sprite.setTextureRect(textureRect);
}

void Tile::rescale(float scale) {
    this->scale = sf::Vector2f(scale, scale);
    sprite.setScale(this->scale*scalePromotion);
}

void Tile::setPosition(sf::Vector2f position) {
    this->position = position;
    sprite.setPosition(position);
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

sf::Vector2i Tile::getSize() {
    return sf::Vector2i(
        sprite.getTextureRect().width * sprite.getScale().x,
        sprite.getTextureRect().height * sprite.getScale().y
    );
}
