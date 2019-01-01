#include "FigureButton.hpp"

void FigureButton::draw(std::shared_ptr<sf::RenderWindow> window) const {

}

bool FigureButton::isMouseOver() const {
    return isMouseOverFlag;
}

void FigureButton::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = true;
}

void FigureButton::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void FigureButton::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isMouseOverFlag = false;
}

bool FigureButton::isDragging() const {
    return isDraggingFlag;
}

void FigureButton::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = true;
}

void FigureButton::drag(sf::Vector2f cursorPosition) {

}

void FigureButton::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    isDraggingFlag = false;
}
