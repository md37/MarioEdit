#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "classes/System/Interface/DrawableInterface.hpp"
#include "classes/System/Interface/DraggableInterface.hpp"
#include "classes/System/Interface/HoverableInterface.hpp"
#include "classes/Editor/Tile.hpp"
#include "classes/Editor/Navigation/Animation/HighlightButtonAnimation.hpp"
#include "classes/Editor/Navigation/Animation/UndoHighlightButtonAnimation.hpp"

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
    sf::RectangleShape border;

    std::shared_ptr<HighlightButtonAnimation> highlightAnimation;
    std::shared_ptr<UndoHighlightButtonAnimation> undoHighlightAnimation;

    void createBorder();

};
