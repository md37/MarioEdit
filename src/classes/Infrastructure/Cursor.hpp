#pragma once

#include <memory>
#include <vector>
#include <any>
#include <SFML/Config.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Circle.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

class Cursor {

public:

    static void reinitialize(std::shared_ptr<sf::RenderWindow> &window);
    void updatePosition(sf::Vector2f currentPosition);
    sf::Vector2f getPosition() const;

    std::any draggedItem;

    Cursor();

    void draw(std::shared_ptr<sf::RenderWindow> window);
    bool isOver(sf::Vector2f position, sf::Vector2u size);
    bool isOver(Circle circle);

    bool isClick();
    void click(bool click, sf::Mouse::Button type);
    sf::Mouse::Button getClickType();

    bool isMouseMoved();
    void mouseMove(bool mouseMove);

    bool isMousePressed();
    void mousePress(bool mouseDown);

    bool isMouseReleased();
    void mouseRelease(bool mouseUp);

    bool isLongClick();

    void resetPressState();
    sf::Time getClickDuration();

private:

    static std::shared_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;

    bool moveFlag = false;

    bool clickFlag = false;
    sf::Mouse::Button clickType = sf::Mouse::Button::Left;
    bool mousePressedFlag = false;
    bool mouseReleasedFlag = false;
    sf::Clock clickClock;
};