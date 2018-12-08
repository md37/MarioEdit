#include "ResizeIndicator.hpp"

#include <iostream>
#include "classes/Infrastructure/Log.hpp"

ResizeIndicator::ResizeIndicator(
    sf::Rect<float> figureArea, IndicatorSide side, std::function<void()> action, bool isActive
) {
    this->figureArea = figureArea;
    this->side = side;
    this->action = action;
    this->isActiveFlag = isActive;

    sf::Color fillColor = isActive ? enabledColor : disabledColor;
    area.setFillColor(fillColor);
    area.setSize(size);

    recalculatePosition();
}

void ResizeIndicator::recalculatePosition() {
    auto position = calculatePosition();
    area.setPosition(position);
}

sf::Vector2f ResizeIndicator::calculatePosition() {
    sf::Vector2f position = {0.0f, 0.0f};

    auto scale = area.getScale();
    auto size = area.getSize();
    size.x *= scale.x;
    size.y *= scale.y;

    switch (side) {
        case TopEdge: {
            position = {
                figureArea.left+figureArea.width/2-size.x/2,
                figureArea.top,
            };
        } break;
        case BottomEdge: {
            position = {
                figureArea.left+figureArea.width/2-size.x/2,
                figureArea.top+figureArea.height-size.y,
            };
        } break;
        case LeftEdge: {
            position = {
                figureArea.left,
                figureArea.top+figureArea.height/2-size.y/2,
            };
        } break;
        case RightEdge: {
            position = {
                figureArea.left+figureArea.width-size.x,
                figureArea.top+figureArea.height/2-size.y/2,
            };
        } break;
        case LeftTopCorner: {
            position = {
                figureArea.left,
                figureArea.top,
            };
        } break;
        case LeftBottomCorner: {
            position = {
                figureArea.left,
                figureArea.top+figureArea.height-size.y,
            };
        } break;
        case RightTopCorner: {
            position = {
                figureArea.left+figureArea.width-size.x,
                figureArea.top,
            };
        } break;
        case RightBottomCorner: {
            position = {
                figureArea.left+figureArea.width-size.x,
                figureArea.top+figureArea.height-size.y,
            };
        } break;
    }
    return position;
}

void ResizeIndicator::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(area);
}

void ResizeIndicator::rescale(std::unique_ptr<Scale> &scale) {
    scaleRatio = scale->getRatio();
    auto newScale = sf::Vector2f(scale->getCurrent(), scale->getCurrent());
    area.setScale(newScale);

    auto position = calculatePosition();
    area.setPosition(position);
}

bool ResizeIndicator::isMouseOver() {
    return isMouseOverFlag;
}

void ResizeIndicator::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
    area.setFillColor(hoverColor);

    Log::out("Indicator MouseEnter");
}

void ResizeIndicator::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    area.setFillColor(hoverColor);
}

void ResizeIndicator::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
    area.setFillColor(enabledColor);
;
    Log::out("Indicator MouseLeave");
}

bool ResizeIndicator::isDragging() {
    return isDraggingFlag;
}

void ResizeIndicator::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = true;
}

void ResizeIndicator::drag(sf::Vector2f cursorPosition) {

}

void ResizeIndicator::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = false;
}

void ResizeIndicator::runAction() {
    if (!isActiveFlag) {
        action();
    }
}

void ResizeIndicator::setFigureArea(sf::Rect<float> figureArea) {
    this->figureArea = figureArea;
}

bool ResizeIndicator::isActive() {
    return isActiveFlag;
}

sf::Vector2f ResizeIndicator::getPosition() {
    return area.getPosition();
}

sf::Vector2u ResizeIndicator::getSize() {
    return sf::Vector2u(area.getSize().x * area.getScale().x, area.getSize().y * area.getScale().y);
}
