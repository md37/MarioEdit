#pragma once

#include <string>
#include <memory>
#include <SFML/Config.hpp>
#include "classes/Scene/Tile/DynamicTile.hpp"
#include "classes/Scene/Tile/StaticTile.hpp"
#include "classes/Tilebar/Tile/ButtonTile.hpp"
#include "classes/TileConfig.hpp"
#include "classes/Scene/Scale.hpp"

class TileFactory
{

public:

    explicit TileFactory(std::string filepath, std::shared_ptr<Scale> scale);

    void setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY);
    void setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY);

    std::shared_ptr<DynamicTile> createDynamicTile(sf::Uint32 x, sf::Uint32 y);
    std::shared_ptr<StaticTile> createStaticTile(sf::Uint32 x, sf::Uint32 y);
    std::shared_ptr<ButtonTile> createButtonTile(sf::Uint32 x, sf::Uint32 y);

private:

    std::shared_ptr<Scale> scale;
    TileConfig config;
    std::shared_ptr<sf::Texture> texture;

    sf::Sprite prepareSprite() const;
};