#pragma once

#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Editor/Object/GridTile.hpp"
#include "classes/Editor/Scene/Animation/HighlightAnimation.hpp"
#include "classes/Editor/Scene/Animation/UndoHighlightAnimation.hpp"

class DynamicTile : public GridTile, HoverableInterface, DraggableInterface, DrawableInterface {

public:

    explicit DynamicTile(sf::Sprite sprite, std::shared_ptr<Grid> grid, TileConfig config=TileConfig());

    bool isBlinking = false;
    bool isReturning = false;

    void rescale(std::unique_ptr<Scale> &newScale) override;

    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isMouseOver() const override;

    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    bool isDragging() const override;

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    sf::Vector2i getDropHighlightPlace() const;

    void correctCorners();

private:

    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2i dropHighlightPlace = {0, 0};

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    std::shared_ptr<HighlightAnimation> highlightAnimation;
    std::shared_ptr<UndoHighlightAnimation> undoHighlightAnimation;
};
