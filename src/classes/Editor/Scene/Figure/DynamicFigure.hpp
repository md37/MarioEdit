#pragma once

#include "classes/Editor/Object/Figure.hpp"

class DynamicFigure : public Figure, HoverableInterface, DraggableInterface {

public:

    explicit DynamicFigure(std::unique_ptr<TileFactory> &tileFactory);

    void drawFrame(std::shared_ptr<sf::RenderWindow> window);

    bool isMouseOver() const override;
    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    bool isDragging() const override;
    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    virtual void changeVariant(sf::Uint8 variant)=0;

    void changeGrid(std::shared_ptr<Grid> grid);

protected:

    sf::RectangleShape frame;

    void resetFrame();

private:

    bool isMouseOverFlag = false;
    bool isFrameCreated = false;

    bool isDraggingFlag = false;
    sf::Vector2f dragOffset = {0.0f, 0.0f};
    sf::Vector2f dragOffsetForHighlight = {0.0f, 0.0f};

    sf::Color frameColorNormal = sf::Color(255, 255, 255, 30);
    sf::Color frameColorError = sf::Color(255, 0, 0, 100);

    void recalculateHighlightPosition(sf::Vector2f cursorPosition) const;
    void calculateDragOffset(sf::Vector2f cursorPosition);
    void moveTiles(sf::Vector2f prevPosition);

    void updateFramePosition();
    void recalculateFramePosition(sf::Vector2f cursorPosition);

    bool checkForCollisions();
};
