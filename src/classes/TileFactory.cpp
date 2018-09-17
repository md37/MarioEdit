#include "TileFactory.hpp"

#include <SFML/Graphics/Texture.hpp>
#include "classes/ObjectRegistry.hpp"
#include "classes/Scene/Tile/DynamicTile.hpp"

TileFactory::TileFactory(std::string filepath, std::shared_ptr<Scale> scale) {
    texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(filepath);
    this->scale = scale;
}

void TileFactory::setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY) {
    config.separatorX = separatorX;
    config.separatorY = separatorY;
}

void TileFactory::setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY) {
    config.offsetX = offsetX;
    config.offsetY = offsetY;
}

std::shared_ptr<DynamicTile> TileFactory::createDynamicTile(sf::Uint32 x, sf::Uint32 y) {
    auto sprite = prepareSprite();
    auto tile = std::make_shared<DynamicTile>(sprite, config);
    tile->changeImage(x, y);
    ObjectRegistry::registerTile(tile);

    return tile;
}

std::shared_ptr<StaticTile> TileFactory::createStaticTile(sf::Uint32 x, sf::Uint32 y) {
    auto sprite = prepareSprite();
    auto tile = std::make_shared<StaticTile>(sprite, config);
    tile->changeImage(x, y);
    ObjectRegistry::registerTile(tile);

    return tile;
}

std::shared_ptr<ButtonTile> TileFactory::createButtonTile(sf::Uint32 x, sf::Uint32 y) {
    auto sprite = prepareSprite();
    auto tile = std::make_shared<ButtonTile>(sprite, config);
    tile->changeImage(x, y);
    ObjectRegistry::registerTile(tile);

    return tile;
}

sf::Sprite TileFactory::prepareSprite() const {
    sf::Sprite sprite;
    sprite.setTexture(*(texture));
    sprite.setScale(scale->getScale(), scale->getScale());
    return sprite;
}
