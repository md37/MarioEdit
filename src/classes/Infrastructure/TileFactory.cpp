#include "TileFactory.hpp"

#include <SFML/Graphics/Texture.hpp>
#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Infrastructure/Log.hpp"

TileFactory::TileFactory(std::string filepath, std::unique_ptr<Scale> &scale) : scale(scale) {
    texture = std::make_unique<sf::Texture>();
    texture->loadFromFile(filepath);
    this->setTileSeparators(1, 1);
}

void TileFactory::setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY) {
    config.separatorX = separatorX;
    config.separatorY = separatorY;
}

void TileFactory::setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY) {
    config.offsetX = offsetX;
    config.offsetY = offsetY;
}

std::shared_ptr<DynamicTile> TileFactory::createDynamicTile(sf::Uint32 x, sf::Uint32 y, std::shared_ptr<Grid>& grid) const {
    Log::out("Creating dynamic tile");

    auto sprite = prepareSprite();
    auto tile = std::make_shared<DynamicTile>(sprite, grid, config);
    tile->changeImage(x, y);
    tile->rescale(scale);
    ObjectRegistry::add(tile);

    tile->isBlinking = x == 0 && y == 11;

    return tile;
}

std::shared_ptr<StaticTile> TileFactory::createStaticTile(sf::Uint32 x, sf::Uint32 y, std::shared_ptr<Grid>& grid) const {
    Log::out("Creating static tile");

    auto sprite = prepareSprite();
    auto tile = std::make_shared<StaticTile>(sprite, grid, config);
    tile->changeImage(x, y);
    ObjectRegistry::add(tile);

    return tile;
}

std::shared_ptr<TileButton> TileFactory::createButtonTile(sf::Uint32 x, sf::Uint32 y) const {
    Log::out("Creating button tile");

    auto sprite = prepareSprite();
    auto tile = std::make_shared<TileButton>(sprite, config);
    tile->changeImage(x, y);
    ObjectRegistry::add(tile);

    return tile;
}

sf::Sprite TileFactory::prepareSprite() const {
    sf::Sprite sprite;
    sprite.setTexture(*(texture));
    sprite.setScale(scale->getCurrent(), scale->getCurrent());
    return sprite;
}
