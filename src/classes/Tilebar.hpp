#pragma once

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Tilebar/Tile/ButtonTile.hpp"
#include "classes/Interface/RescalableInterface.hpp"
#include "classes/Interface/DrawableInterface.hpp"

class Tilebar : public RescalableInterface, public DrawableInterface {

public:

    explicit Tilebar(std::shared_ptr<sf::RenderWindow> window);
    void rescale(sf::Vector2u windowSize) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

private:

    sf::RectangleShape box;
    sf::Uint32 boxHeight;
    float lineThicknessDivider = 1200;

    std::vector<std::shared_ptr<ButtonTile>> tiles;

    void generateBox(std::shared_ptr<sf::RenderWindow> window);
    void drawDynamicTiles(std::shared_ptr<sf::RenderWindow> &window) const;
};
