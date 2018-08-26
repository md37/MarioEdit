#pragma once

#include "classes/Tile.hpp"
#include "classes/Animation/SmoothAnimation/HighlightTileAnimation.hpp"
#include "classes/Animation/SmoothAnimation/UndoHighlightTileAnimation.hpp"

class DynamicTile : public Tile {

public:

    enum Event {
        MouseOver,
        MouseEnter,
        MouseLeave,
        StartDrag,
        Drag,
        Drop,
    };

    DynamicTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void handleEvent(DynamicTile::Event event);
    void addEventHandler(DynamicTile::Event event, std::function<void(DynamicTile *tile)> callback);

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

private:

    sf::Vector2f dragOffset = {0.0f, 0.0f};

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::map<Event, std::function<void(DynamicTile* tile)>> eventCallbacks;

    std::shared_ptr<HighlightTileAnimation> highlightTileAnimation;
    std::shared_ptr<UndoHighlightTileAnimation> undoHighlightTileAnimation;

};
