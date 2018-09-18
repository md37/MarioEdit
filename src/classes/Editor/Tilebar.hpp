#pragma once

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Tilebar/Tile/ButtonTile.hpp"
#include "classes/Editor/TileFactory.hpp"
#include "classes/Interface/RescalableInterface.hpp"
#include "classes/Interface/DrawableInterface.hpp"

class Tilebar : public RescalableInterface, public DrawableInterface {

public:

    explicit Tilebar(std::shared_ptr<TileFactory> tileFactory);
    void rescale(sf::Vector2u windowSize) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

private:

    sf::RectangleShape box;
    sf::Uint32 boxHeight;
    float lineThicknessDivider = 1200;

    std::shared_ptr<TileFactory> tileFactory;
    std::vector<std::shared_ptr<ButtonTile>> tiles;

    void generateBox();
    void generateDynamicTileButtons();

    void drawDynamicTileButtons(std::shared_ptr<sf::RenderWindow> &window) const;
};
