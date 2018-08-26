#pragma once

#include <string>
#include <memory>
#include <SFML/Config.hpp>
#include "classes/Tile/DynamicTile.hpp"
#include "classes/Tile/TileConfig.hpp"

class TileFactory
{

public:

    explicit TileFactory(std::string filepath);

    void setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY);
    void setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY);

    std::shared_ptr<DynamicTile> createDynamicTile(sf::Uint32 x, sf::Uint32 y);

private:

    TileConfig config;
    std::shared_ptr<sf::Texture> texture;

};