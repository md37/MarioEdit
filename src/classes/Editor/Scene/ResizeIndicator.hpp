#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "classes/Infrastructure/Interface/CircleableInterface.hpp"
#include "classes/Infrastructure/Interface/DrawableInterface.hpp"
#include "classes/Infrastructure/Interface/RescalableInterface.hpp"
#include "classes/Infrastructure/Interface/HoverableInterface.hpp"
#include "classes/Infrastructure/Interface/DraggableInterface.hpp"

class ResizeIndicator : public CircleableInterface, DrawableInterface, RescalableInterface, HoverableInterface, DraggableInterface {

public:

    ResizeIndicator(sf::Vector2f position, sf::Uint32 radius);
    Circle getCircle() override;

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

private:

    sf::Color color;
    sf::Vector2f position = {0, 0};
    sf::Uint32 radius = 30;

    bool isMouseOverFlag = false;
    bool isDraggingFlag = false;

    sf::CircleShape borderCircle;
    sf::CircleShape dotCircle;
    float dotCircleRadiusMultiplier = 0.25f;

    void changeColor(sf::Color color);

};
