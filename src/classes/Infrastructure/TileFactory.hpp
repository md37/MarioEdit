#pragma once

#include <string>
#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "classes/Infrastructure/Scale.hpp"
#include "classes/Infrastructure/TileConfig.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Scene/Tile/StaticTile.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"

class ButtonTile;

class TileFactory {

public:

    explicit TileFactory(std::string filepath, std::unique_ptr<Scale> &scale);

    void setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY);
    void setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY);

    std::shared_ptr<DynamicTile> createDynamicTile(sf::Uint32 x, sf::Uint32 y, std::unique_ptr<Grid>& grid) const;
    std::shared_ptr<StaticTile> createStaticTile(sf::Uint32 x, sf::Uint32 y, std::unique_ptr<Grid>& grid) const;
    std::shared_ptr<ButtonTile> createButtonTile(sf::Uint32 x, sf::Uint32 y) const;

private:

    std::unique_ptr<Scale> &scale;
    TileConfig config;
    std::unique_ptr<sf::Texture> texture;

    sf::Sprite prepareSprite() const;
};