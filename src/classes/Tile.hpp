#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <memory>
#include <functional>
#include "classes/Grid.hpp"
#include "classes/Tile/TileConfig.hpp"

class Tile {

public:

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    Tile(sf::Sprite sprite, TileConfig config=TileConfig());

    float scalePromotion = 1.0f;

    void changeImage(sf::Uint32 x, sf::Uint32 y);
    void rescale(float scale);
    void draw(std::shared_ptr<sf::RenderWindow> window);

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    sf::Vector2i getSize();

    void setGrid(std::shared_ptr<Grid> grid);
    void snapToGrid();
    void snapToGrid(sf::Vector2u gridPosition);

protected:

    static std::shared_ptr<sf::RenderWindow> window;

    sf::Sprite sprite;
    sf::Vector2f scale = {1.0f, 1.0f};
    sf::Vector2f position;

    std::shared_ptr<Grid> grid;
    sf::Vector2u gridPosition;

private:

    TileConfig config;

};
