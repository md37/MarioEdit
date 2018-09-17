#pragma once

#include "classes/Interface/HoverableInterface.hpp"
#include "classes/Interface/DraggableInterface.hpp"
#include "classes/Interface/DrawableInterface.hpp"
#include "classes/Scene/Tile/GridTile.hpp"
#include "classes/Animation/SmoothAnimation/HighlightTileAnimation.hpp"
#include "classes/Animation/SmoothAnimation/UndoHighlightTileAnimation.hpp"

class DynamicTile : public GridTile, public HoverableInterface, public DraggableInterface, DrawableInterface {

public:

    enum Event {
        MouseOver,
        MouseEnter,
        MouseLeave,
        StartDrag,
        Drag,
        Drop,
    };

    explicit DynamicTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void handleEvent(DynamicTile::Event event);
    void addEventHandler(DynamicTile::Event event, std::function<void(DynamicTile *tile)> callback);

    bool isBlinking = false;

    bool isMouseOver();
    bool isDragging();

    void mouseEnter() override;
    void mouseLeave() override;
    void startDrag() override;
    void drag() override;
    void drop() override;

    void correctCorners();

private:

    sf::Vector2f dragOffset = {0.0f, 0.0f};

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::map<Event, std::function<void(DynamicTile* tile)>> eventCallbacks;

    std::shared_ptr<HighlightTileAnimation> highlightTileAnimation;
    std::shared_ptr<UndoHighlightTileAnimation> undoHighlightTileAnimation;

};
