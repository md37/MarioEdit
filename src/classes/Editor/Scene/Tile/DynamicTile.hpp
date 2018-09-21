#pragma once

#include "classes/System/Interface/HoverableInterface.hpp"
#include "classes/System/Interface/DraggableInterface.hpp"
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/Editor/Scene/Tile/GridTile.hpp"
#include "classes/Editor/Scene/Animation/HighlightAnimation.hpp"
#include "classes/Editor/Scene/Animation/UndoHighlightAnimation.hpp"

class DynamicTile : public GridTile, public HoverableInterface, public DraggableInterface, DrawableInterface {

public:

    explicit DynamicTile(sf::Sprite sprite, TileConfig config=TileConfig());

    bool isBlinking = false;
    bool isReturning = false;

    void mouseEnter() override;
    void mouseOver() override;
    void mouseLeave() override;
    bool isMouseOver() override;

    void startDrag() override;
    void drag() override;
    void drop() override;
    bool isDragging() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void correctCorners();
    sf::Vector2u getDropHighlightPlace();

private:

    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2u dropHighlightPlace = {0, 0};

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::shared_ptr<HighlightAnimation> highlightAnimation;
    std::shared_ptr<UndoHighlightAnimation> undoHighlightAnimation;

};
