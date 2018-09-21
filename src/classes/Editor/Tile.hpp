#pragma once

#include <map>
#include <memory>
#include <functional>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "classes/System/TileConfig.hpp"
#include "classes/Editor/Scene/Grid.hpp"

class Tile {

public:

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    explicit Tile(sf::Sprite sprite, TileConfig config=TileConfig());

    float scalePromotion = 1.0f;

    void changeImage(sf::Uint32 x, sf::Uint32 y);
    void rescale(float scale);

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    sf::Vector2i getSize();

protected:

    static std::shared_ptr<sf::RenderWindow> window;

    void recalculateCenter();

    sf::Sprite sprite;
    sf::Vector2f scale = {1.0f, 1.0f};
    sf::Vector2f position;
    sf::Vector2f centerPoint;

private:

    TileConfig config;

};
