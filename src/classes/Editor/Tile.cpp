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

void Tile::rescale(std::shared_ptr<Scale>& newScale) {
    auto scaleRatio = newScale->getRatio();
    auto position = getPosition();
    sprite.setPosition(position*scaleRatio);

    scale = sf::Vector2f(newScale->getCurrent(), newScale->getCurrent());
    sprite.setScale(scale*scalePromotion);

    if (borderSize > 0) {
        auto newBorderSize = borderSize*newScale->getCurrent()*scalePromotion;
        auto borderSquareSize = sf::Vector2f(getSize());
        borderSquareSize.x += 2*newBorderSize;
        borderSquareSize.y += 2*newBorderSize;
        border.setSize(borderSquareSize);

        auto borderSquarePosition = sf::Vector2f(position*scaleRatio);
        borderSquarePosition.x -= newBorderSize;
        borderSquarePosition.y -= newBorderSize;
        border.setPosition(borderSquarePosition);
    }
}

void Tile::recalculateCenter() {
    auto position = getPosition();
    centerPoint.x = position.x + getSize().x/2;
    centerPoint.y = position.y + getSize().y/2;
}

void Tile::changeImage(sf::Uint32 x, sf::Uint32 y) {
    sf::IntRect textureRect;
    textureRect.width = config.tileWidth;
    textureRect.height = config.tileHeight;

    textureRect.top = (y * (config.tileHeight+config.separatorY)) + config.offsetY;
    textureRect.left = (x * (config.tileWidth+config.separatorX)) + config.offsetX;
    sprite.setTextureRect(textureRect);

    imagePosition = sf::Vector2u(x, y);
}

void Tile::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
    recalculateCenter();
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

sf::Vector2u Tile::getSize() {
    return sf::Vector2u(
        sprite.getTextureRect().width * sprite.getScale().x,
        sprite.getTextureRect().height * sprite.getScale().y
    );
}

void Tile::setBorder(sf::Uint8 size, sf::Color color) {
    borderSize = size;
    border.setFillColor(color);
}

void Tile::snapToCenterPoint() {
    auto newSpriteScale = scale*scalePromotion;
    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    sprite.setScale(newSpriteScale.x, newSpriteScale.y);

    auto position = getPosition();
    position.x = centerPoint.x-newWidth/2;
    position.y = centerPoint.y-newHeight/2;
    sprite.setPosition(position);
}

bool Tile::isTypeOf(std::shared_ptr<Tile> tile) {
    return imagePosition == tile->imagePosition;
}
