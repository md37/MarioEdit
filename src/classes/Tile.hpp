#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <memory>
#include <functional>
#include "classes/Grid.hpp"
#include "classes/Tile/TileConfig.hpp"
#include "classes/Animation/SmoothAnimation/HighlightTileAnimation.hpp"
#include "classes/Animation/SmoothAnimation/UndoHighlightTileAnimation.hpp"

class Tile
{

public:

    enum Event {
        MouseOver,
        MouseEnter,
        MouseLeave,
        StartDrag,
        Drag,
        Drop,
    };

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    Tile(sf::Sprite sprite, TileConfig config = TileConfig());

    float scalePromotion = 1.0f;

    void change(sf::Uint32 x, sf::Uint32 y);

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    void setGrid(std::shared_ptr<Grid> grid);
    void snapToGrid();
    void snapToGrid(sf::Vector2u gridPosition);

    sf::Vector2i getSize();

    void rescale(float scale);

    void draw(std::shared_ptr<sf::RenderWindow> window);
    void handleEvent(Tile::Event event);
    void setEventHandler(Tile::Event event, std::function<void(Tile* tile)> callback);

    bool isMouseOver();
    bool isDragging();

    void highlight();
    void undoHighlight();
    void startDrag();
    void drag();
    void drop();

    void snapToCenterPoint();
    void correctCorners();

    void snapToWindowBound();

private:

    static std::shared_ptr<sf::RenderWindow> window;

    TileConfig config;
    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2f position;
    
    std::shared_ptr<Grid> grid;
    sf::Vector2u gridPosition;

    sf::Vector2f scale = {1.0f, 1.0f};

    sf::Sprite sprite;

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::map<Event, std::function<void(Tile* tile)>> eventCallbacks;

    std::shared_ptr<HighlightTileAnimation> highlightTileAnimation;
    std::shared_ptr<UndoHighlightTileAnimation> undoHighlightTileAnimation;

    bool isOnLeftEdge();
    bool isOnRightEdge();
    bool isOnTopEdge();
    bool isOnBottomEdge();

    bool isOnTopLeftCorner();
    bool isOnBottomLeftCorner();
    bool isOnBottomRightCorner();
    bool isOnTopRightCorner();

    void snapToTopLeftCorner();
    void snapToBottomLeftCorner();
    void snapToBottomRightCorner();
    void snapToTopRightCorner();

    void snapToLeftEdge();
    void snapToRightEdge();
    void snapToTopEdge();
    void snapToBottomEdge();
};
