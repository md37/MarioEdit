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

    void mouseEnter(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void mouseOver(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void mouseLeave(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    bool isMouseOver() override;

    void startDrag(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    void drag() override;
    void drop(std::shared_ptr<AnimationPerformer> animationPerformer) override;
    bool isDragging() override;

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    sf::Vector2u getDropHighlightPlace();

    void correctCorners();

private:

    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2u dropHighlightPlace = {0, 0};

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::shared_ptr<HighlightAnimation> highlightAnimation;
    std::shared_ptr<UndoHighlightAnimation> undoHighlightAnimation;

};
