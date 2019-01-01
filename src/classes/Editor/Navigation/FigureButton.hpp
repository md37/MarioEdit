#pragma once

#include "classes/Editor/Object/StaticFigure.hpp"
#include "classes/Editor/Navigation/AbstractButton.hpp"

class FigureButton : public StaticFigure, AbstractButton {

public:

    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    bool isMouseOver() const override;

    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    bool isDragging() const override;

    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

private:

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

};
