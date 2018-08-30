#include "TileFactory.hpp"

#include <SFML/Graphics/Texture.hpp>
#include "classes/Scene/Tile/DynamicTile.hpp"
#include "classes/Scene/Tile/TileRegistry.hpp"

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
    sf::Sprite sprite;
    sprite.setTexture(*(texture));
    sprite.setScale(scale->getScale(), scale->getScale());

    auto tile = std::make_shared<DynamicTile>(sprite, config);
    tile->changeImage(x, y);
    TileRegistry::registerTile(tile);

    return tile;
}
