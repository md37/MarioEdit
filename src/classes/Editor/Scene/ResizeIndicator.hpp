#pragma once

#include <functional>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "defines.hpp"
#include "classes/Infrastructure/Interface/CircleableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"

class ResizeIndicator : public DrawableInterface, RescalableInterface, HoverableInterface, DraggableInterface {

public:

    enum IndicatorSide {
        TopEdge = BIT(0),
        BottomEdge = BIT(1),
        LeftEdge = BIT(2),
        LeftTopCorner = BIT(3),
        LeftBottomCorner = BIT(4),
        RightEdge = BIT(5),
        RightTopCorner = BIT(6),
        RightBottomCorner = BIT(7),
    };

    ResizeIndicator(
        sf::Rect<float> figureArea, IndicatorSide side, std::function<void()> action, bool enabled
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
    void recalculatePosition();
    void setFigureArea(sf::Rect<float> figureArea);

private:

    float scaleRatio = 1.0f;
    sf::Color enabledColor = sf::Color(255, 255, 255, 240);
    sf::Color disabledColor = sf::Color(255, 255, 255, 70);
    sf::Vector2f size = {2.0f, 2.0f};

    sf::Rect<float> figureArea;
    IndicatorSide side;
    std::function<void()> action;
    bool enabled;

    sf::RectangleShape area;

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;
    sf::Vector2f calculatePosition();
};
