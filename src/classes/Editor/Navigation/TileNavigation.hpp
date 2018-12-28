#pragma once

#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/Infrastructure/TileFactory.hpp"

class TileNavigation : Navigation {

public:

    explicit TileNavigation(std::unique_ptr<TileFactory> &tileFactory);

    void rescale(std::unique_ptr<Scale>& scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

private:

    sf::RectangleShape box;
    sf::Uint32 boxWidth = 420;
    sf::Uint32 boxHeight = 120;
    std::unique_ptr<TileFactory> &tileFactory;

    void generateBox();
    void generateTileButtons();

    void drawTileButtons(std::shared_ptr<sf::RenderWindow> &window) const;

};
