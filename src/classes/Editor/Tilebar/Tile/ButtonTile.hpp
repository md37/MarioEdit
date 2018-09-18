#pragma once

#include "classes/Interface/DrawableInterface.hpp"
#include "classes/Interface/DraggableInterface.hpp"
#include "classes/Interface/HoverableInterface.hpp"
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Tilebar/Animation/HighlightButtonAnimation.hpp"
#include "classes/Editor/Tilebar/Animation/UndoHighlightButtonAnimation.hpp"

class ButtonTile : public Tile, public DrawableInterface, public DraggableInterface, public HoverableInterface {

public:

    explicit ButtonTile(sf::Sprite sprite, TileConfig config=TileConfig());

    void mouseEnter() override;
    void mouseOver() override;
    void mouseLeave() override;
    bool isMouseOver() override;

    void startDrag() override;
    void drag() override;
    void drop() override;
    bool isDragging() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

private:

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::shared_ptr<HighlightButtonAnimation> highlightAnimation;
    std::shared_ptr<UndoHighlightButtonAnimation> undoHighlightAnimation;

};
