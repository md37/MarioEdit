#pragma once

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Navigation/AbstractNavigation.hpp"
#include "classes/Editor/Navigation/TileButton.hpp"
#include "classes/Infrastructure/TileFactory.hpp"

class TileNavigation : AbstractNavigation {

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
