#pragma once

#include <memory>
#include <vector>
#include <variant>
#include <SFML/Config.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <optional>
#include "classes/Editor/Scene/Figure/Bush.hpp"
#include "classes/Editor/Scene/Figure/Cloud.hpp"
#include "classes/Editor/Scene/Figure/Hill.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/Infrastructure/Circle.hpp"

class Cursor {

public:

    static void reinitialize(std::shared_ptr<sf::RenderWindow> &window);
    void updatePosition(sf::Vector2f currentPosition);
    sf::Vector2f getPosition() const;

    std::optional<
        std::variant<std::shared_ptr<DynamicTile>, std::shared_ptr<Figure>>
    >draggedItem;

    Cursor();

    void draw(std::shared_ptr<sf::RenderWindow> window);
    bool isOver(sf::Vector2f position, sf::Vector2u size) const;
    bool isOver(Circle circle) const;

    bool isClick() const;
    void click(bool click, sf::Mouse::Button type);
    sf::Mouse::Button getClickType() const;

    bool isMouseMoved() const;
    void mouseMove(bool mouseMove);

    bool isMousePressed() const;
    void mousePress(bool mouseDown);

    bool isMouseReleased() const;
    void mouseRelease(bool mouseUp);

    bool isLongClick() const;

    void resetPressState();
    sf::Time getClickDuration() const;

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