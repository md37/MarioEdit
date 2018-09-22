#pragma once

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/System/TileFactory.hpp"
#include "classes/System/Interface/RescalableInterface.hpp"
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"

class Navigation : public RescalableInterface, public DrawableInterface {

public:

    explicit Navigation(std::shared_ptr<TileFactory> tileFactory);
    void rescale(std::shared_ptr<Scale> scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

private:

    sf::RectangleShape box;
    sf::Uint32 boxHeight;
    float lineThicknessDivider = 1200;

    std::shared_ptr<TileFactory> tileFactory;
    std::vector<std::shared_ptr<ButtonTile>> tiles;

    void generateBox();
    void generateTileButtons();

    void drawTileButtons(std::shared_ptr<sf::RenderWindow> &window) const;
};
