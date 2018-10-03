#pragma once

#include <memory>
#include <vector>
#include <SFML/Config.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Mouse.hpp>
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

class Cursor {

public:

    static void reinitialize(std::shared_ptr<sf::RenderWindow> &window);
    static sf::Vector2f getCurrentPosition();

    Cursor();

    void draw(std::shared_ptr<sf::RenderWindow> window);
    bool isOver(std::shared_ptr<Tile> tile);
    bool isClickOn(std::shared_ptr<Tile> tile);

    bool isClick();
    void click(bool click, sf::Mouse::Button type);
    sf::Mouse::Button getClickType();
    bool isMousePressed();
    void mousePress(bool mouseDown);
    bool isMouseReleased();
    void mouseRelease(bool mouseUp);

    void registerOver(std::shared_ptr<Tile> tile);
    void unregisterOver(std::shared_ptr<Tile> tile);
    bool isOverRegistered(std::shared_ptr<Tile> tile);

    void registerDrag(std::shared_ptr<DynamicTile> tile);
    void unregisterDrag(std::shared_ptr<DynamicTile> tile);
    bool isDragRegistered(std::shared_ptr<DynamicTile> tile);

    void handleRegisteredDrags();

    bool isLongClick();

    void resetPressState();
    sf::Time getClickDuration();

private:

    static std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;

    std::vector<std::shared_ptr<Tile>> registeredOverOnTiles;
    std::vector<std::shared_ptr<DynamicTile>> registeredDragOnTiles;

    bool clickFlag;
    sf::Mouse::Button clickType;
    bool mousePressedFlag = false;
    bool mouseReleasedFlag = false;
    sf::Clock clickClock;

    void updatePosition();
};