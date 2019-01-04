#pragma once

#include <string>
#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "classes/Infrastructure/Scale.hpp"
#include "classes/Infrastructure/TileConfig.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Editor/Object/StaticTile.hpp"
#include "classes/Editor/Navigation/TileButton.hpp"

class TileButton;

class TileFactory {

public:

    explicit TileFactory(std::string filepath, std::unique_ptr<Scale> &scale);

    void setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY);
    void setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY);

    std::shared_ptr<DynamicTile> createDynamicTile(sf::Uint32 x, sf::Uint32 y, std::shared_ptr<Grid> grid) const;
    std::shared_ptr<StaticTile> createStaticTile(sf::Uint32 x, sf::Uint32 y, std::shared_ptr<Grid> grid) const;
    std::shared_ptr<TileButton> createButtonTile(sf::Uint32 x, sf::Uint32 y) const;

private:

    std::unique_ptr<Scale> &scale;
    TileConfig config;
    std::unique_ptr<sf::Texture> texture;

    sf::Sprite prepareSprite() const;
};