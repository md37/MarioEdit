#include "ResizeIndicator.hpp"

#include <iostream>

ResizeIndicator::ResizeIndicator(
    sf::Rect<float> figureArea,
    IndicatorSide side,
    MoveDirection moveDirection,
    std::function<void()> action
) {
    this->figureArea = figureArea;
    this->side = side;
    this->moveDirection = moveDirection;
    this->action = action;

    prepareArea();
}

void ResizeIndicator::prepareArea() {
    sf::Vector2f areaPosition;
    sf::Vector2f areaSize;

    switch (side) {
        case Top: {
            areaPosition = {figureArea.left, figureArea.top};
            areaSize = {figureArea.width, figureArea.height * sizeMultiplier};

        } break;
        case Left: {
            areaPosition = {figureArea.left, figureArea.top};
            areaSize = {figureArea.width * sizeMultiplier, figureArea.height};
        } break;
        case Bottom: {
            auto posY = figureArea.top+figureArea.height;
            posY -= figureArea.height * sizeMultiplier;
            areaPosition = {figureArea.left, posY};

            areaSize = {figureArea.width, figureArea.height * sizeMultiplier};
        } break;
        case Right: {
            auto posX = figureArea.left+figureArea.width;
            posX -= figureArea.width * sizeMultiplier;
            areaPosition = {posX, figureArea.top};

            areaSize = {figureArea.width * sizeMultiplier, figureArea.height};
        } break;
    }

    area.setPosition(areaPosition);
    area.setSize(areaSize);
    area.setFillColor(sf::Color(255, 255, 255, 100));
}

void ResizeIndicator::draw(std::shared_ptr<sf::RenderWindow> window) {
    if (isMouseOver()) {
        window->draw(area);
    }
}

void ResizeIndicator::rescale(std::unique_ptr<Scale> &scale) {

}

bool ResizeIndicator::isMouseOver() {
    return isMouseOverFlag;
}

void ResizeIndicator::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
}

void ResizeIndicator::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void ResizeIndicator::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
}

bool ResizeIndicator::isDragging() {
    return isDraggingFlag;
}

void ResizeIndicator::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = true;
    area.setFillColor(sf::Color(255, 255, 0, 128));
}

void ResizeIndicator::drag(sf::Vector2f cursorPosition) {

}

void ResizeIndicator::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = false;
    area.setFillColor(sf::Color(255, 255, 255, 100));
}

void ResizeIndicator::runAction() {
    action();
}
