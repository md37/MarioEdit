#pragma once

#include <memory>
#include <vector>
#include <SFML/Config.hpp>
#include "classes/Scene/Tile/DynamicTile.hpp"
#include "classes/Interface/DrawableInterface.hpp"

class Cursor {

public:

    static void reinitialize(std::shared_ptr<sf::RenderWindow> &window);
    static sf::Vector2f getCurrentPosition();

    Cursor();

    void draw(std::shared_ptr<sf::RenderWindow> window);
    bool isOver(std::shared_ptr<DynamicTile> tile);

    bool isClick();
    void click(bool click);

    void registerOver(std::shared_ptr<DynamicTile> tile);
    void unregisterOver(std::shared_ptr<DynamicTile> tile);
    bool isOverRegistered(std::shared_ptr<DynamicTile> tile);

    void registerDrag(std::shared_ptr<DynamicTile> tile);
    void unregisterDrag(std::shared_ptr<DynamicTile> tile);
    bool isDragRegistered(std::shared_ptr<DynamicTile> tile);

    void handleRegisteredDrags();

private:

    static std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;

    std::vector<std::shared_ptr<DynamicTile>> registeredOverOnTiles;
    std::vector<std::shared_ptr<DynamicTile>> registeredDragOnTiles;

    bool clickFlag;

    void updatePosition();
};