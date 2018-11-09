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

    void rescale(std::unique_ptr<Scale> &newScale);

    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isMouseOver() override;

    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isDragging() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    sf::Vector2i getDropHighlightPlace();

    void correctCorners();

private:

    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2i dropHighlightPlace = {0, 0};

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::shared_ptr<HighlightAnimation> highlightAnimation;
    std::shared_ptr<UndoHighlightAnimation> undoHighlightAnimation;
};
