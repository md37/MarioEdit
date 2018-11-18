#pragma once

#include <functional>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "classes/Infrastructure/Interface/CircleableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"

class ResizeIndicator : public DrawableInterface, RescalableInterface, HoverableInterface, DraggableInterface {

public:

    enum IndicatorSide {
        Top=1,
        Left,
        Bottom,
        Right,
    };

    enum MoveDirection {
        Horizontal=1,
        Vertical,
        DiagonalUp,
        DiagonalDown,
    };

    ResizeIndicator(
        sf::Rect<float> figureArea,
        IndicatorSide side,
        MoveDirection moveDirection,
        std::function<void()> action
    );

    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void rescale(std::unique_ptr<Scale> &scale) override;

    bool isMouseOver() override;
    void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    bool isDragging() override;
    void startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) override;
    void drag(sf::Vector2f cursorPosition) override;
    void drop(std::unique_ptr<AnimationPerformer> &animationPerformer) override;

    void runAction();

private:

    float sizeMultiplier = 0.12;

    sf::Rect<float> figureArea;
    IndicatorSide side;
    MoveDirection moveDirection;
    std::function<void()> action;

    sf::RectangleShape area;

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    void prepareArea();
};
