#pragma once

#include <map>
#include <memory>
#include <functional>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/System/TileConfig.hpp"
#include "classes/System/Scale.hpp"
#include "classes/Editor/Scene/Grid.hpp"

class Tile {

public:

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    explicit Tile(sf::Sprite sprite, TileConfig config=TileConfig());

    float scalePromotion = 1.0f;

    void changeImage(sf::Uint32 x, sf::Uint32 y);
    void rescale(std::shared_ptr<Scale>& scale);

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    sf::Vector2i getSize();

    void setBorder(sf::Uint8 size, sf::Color color=sf::Color(255, 255, 255, 255));
    void snapToCenterPoint();

protected:

    static std::shared_ptr<sf::RenderWindow> window;

    void recalculateCenter();

    sf::Sprite sprite;
    sf::Vector2f scale = {1.0f, 1.0f};
    sf::Vector2f position;
    sf::Vector2f centerPoint;

    sf::RectangleShape border;
    sf::Uint8 borderSize;

    sf::Vector2u imagePosition;

private:

    TileConfig config;

};
