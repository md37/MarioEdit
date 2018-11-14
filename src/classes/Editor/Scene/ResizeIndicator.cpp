#include "ResizeIndicator.hpp"

ResizeIndicator::ResizeIndicator(sf::Vector2f position, sf::Uint32 radius) {
    auto borderPosition = position;
    borderPosition.x -= radius;
    borderPosition.y -= radius;

    auto dotPosition = borderPosition;
    dotPosition.x += radius-dotCircleRadiusMultiplier*radius;
    dotPosition.y += radius-dotCircleRadiusMultiplier*radius;

    this->position = dotPosition;
    this->radius = radius;

    changeColor(sf::Color::White);
    borderCircle.setFillColor(sf::Color::Transparent);
    borderCircle.setOutlineThickness(5);
    borderCircle.setRadius(radius);
    borderCircle.setPosition(borderPosition);
    dotCircle.setRadius(dotCircleRadiusMultiplier*radius);
    dotCircle.setPosition(dotPosition);
}

Circle ResizeIndicator::getCircle() {
    return Circle(position, radius);
}

void ResizeIndicator::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(borderCircle);
    window->draw(dotCircle);
}

void ResizeIndicator::rescale(std::unique_ptr<Scale> &scale) {
    auto ratio = scale->getRatio();

    borderCircle.setPosition(borderCircle.getPosition()*ratio);
    borderCircle.setRadius(borderCircle.getRadius()*ratio);
    borderCircle.setOutlineThickness(borderCircle.getOutlineThickness()*ratio);

    dotCircle.setRadius(dotCircle.getRadius()*ratio);
    dotCircle.setPosition(dotCircle.getPosition()*ratio);
}

bool ResizeIndicator::isMouseOver() {
    return isMouseOverFlag;
}

void ResizeIndicator::mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    changeColor(sf::Color::White);
    isMouseOverFlag = true;
}

void ResizeIndicator::mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer) {

}

void ResizeIndicator::mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    changeColor(sf::Color(255, 255, 255, 100));
    isMouseOverFlag = false;
}

bool ResizeIndicator::isDragging() {
    return isDraggingFlag;
}

void ResizeIndicator::startDrag(sf::Vector2f cursorPosition, std::unique_ptr<AnimationPerformer> &animationPerformer) {
    color = sf::Color::Yellow;
    isDraggingFlag = true;
}

void ResizeIndicator::drag(sf::Vector2f cursorPosition) {

}

void ResizeIndicator::drop(std::unique_ptr<AnimationPerformer> &animationPerformer) {
    changeColor(sf::Color::White);
    isDraggingFlag = false;
}

void ResizeIndicator::changeColor(sf::Color color) {
    borderCircle.setOutlineColor(color);
    dotCircle.setFillColor(color);
}
