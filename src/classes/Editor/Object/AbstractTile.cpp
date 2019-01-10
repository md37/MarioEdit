#include "AbstractTile.hpp"

#include <SFML/Graphics/Texture.hpp>
#include "classes/Infrastructure/Log.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

std::shared_ptr<sf::RenderWindow> AbstractTile::window;

void AbstractTile::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
    AbstractTile::window = window;
}

AbstractTile::AbstractTile(sf::Sprite sprite, TileConfig config) {
    this->sprite = sprite;
    this->config = config;
}

void AbstractTile::rescale(std::unique_ptr<Scale> &newScale) {
    Log::out("Rescaling tile");

    auto scaleRatio = newScale->getRatio();
    auto position = getPosition();
    sprite.setPosition(position * scaleRatio);

    scale = sf::Vector2f(newScale->getCurrent(), newScale->getCurrent());
    sprite.setScale(scale * scalePromotion);

    recalculateCenter();
}

void AbstractTile::setScalePromotion(float scalePromotion) {
    this->scalePromotion = scalePromotion;

    auto newSpriteScale = scale * scalePromotion;
    sprite.setScale(newSpriteScale.x, newSpriteScale.y);
}

float AbstractTile::getScalePromotion() const {
    return scalePromotion;
}

void AbstractTile::recalculateCenter() {
    auto position = getPosition();
    centerPoint.x = position.x + getSize().x / 2;
    centerPoint.y = position.y + getSize().y / 2;
}

void AbstractTile::changeImage(sf::Uint32 x, sf::Uint32 y) {
    sf::IntRect textureRect;
    textureRect.width = config.tileWidth;
    textureRect.height = config.tileHeight;

    textureRect.top = (y * (config.tileHeight + config.separatorY)) + config.offsetY;
    textureRect.left = (x * (config.tileWidth + config.separatorX)) + config.offsetX;
    sprite.setTextureRect(textureRect);

    imagePosition = sf::Vector2u(x, y);
}

sf::Vector2u AbstractTile::getImageCoords() {
    return imagePosition;
}

void AbstractTile::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}

sf::Vector2f AbstractTile::getPosition() const {
    return sprite.getPosition();
}

sf::Vector2u AbstractTile::getSize() const {
    return sf::Vector2u(
            sprite.getTextureRect().width * sprite.getScale().x,
            sprite.getTextureRect().height * sprite.getScale().y
    );
}

void AbstractTile::snapToCenterPoint() {
    auto position = getPosition();

    position.x = centerPoint.x - getSize().x / 2;
    position.y = centerPoint.y - getSize().y / 2;
    sprite.setPosition(position);
}

bool AbstractTile::isTypeOf(std::shared_ptr<AbstractTile> tile) const {
    return imagePosition == tile->imagePosition;
}
