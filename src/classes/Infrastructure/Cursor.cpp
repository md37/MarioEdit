#include "Cursor.hpp"

#include <cmath>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

std::shared_ptr<sf::RenderWindow> Cursor::window;

void Cursor::reinitialize(std::shared_ptr<sf::RenderWindow> &window) {
    Cursor::window = window;
    Cursor::window->setMouseCursorVisible(false);
}

Cursor::Cursor() {
    sprite = std::make_unique<sf::Sprite>();

    float scale = 0.15;
    sprite->scale(scale, scale);
    sprite->setPosition(sf::Vector2f(0, 0));
}

void Cursor::updatePosition(sf::Vector2f mousePosition) {
    sprite->setPosition(mousePosition);
}

sf::Vector2f Cursor::getPosition() const {
    return sprite->getPosition();
}

void Cursor::draw(std::shared_ptr<sf::RenderWindow> window) {
    if (texture == nullptr) {
        texture = std::make_unique<sf::Texture>();
        texture->loadFromFile("resources/cursor.png");
        sprite->setTexture(*texture);
    }
    window->draw(*sprite);
}

bool Cursor::isMouseMoved() const {
    return moveFlag;
}

void Cursor::mouseMove(bool mouseMove) {
    moveFlag = mouseMove;
}

bool Cursor::isOver(sf::Vector2f position, sf::Vector2u size) const {
    auto mousePosition = getPosition();
    auto posX = mousePosition.x;
    auto posY = mousePosition.y;

    return posX >= position.x && posY >= position.y &&
           posX <= position.x+size.x &&
           posY <= position.y+size.y;
}

bool Cursor::isOver(Circle circle) const {
    auto mousePosition = getPosition();

    auto diff = mousePosition-circle.getPosition();
    auto diagonal = sqrt(diff.x*diff.x + diff.y*diff.y);

    return diagonal <= circle.getRadius();
}

bool Cursor::isClick() const {
    return clickFlag;
}

void Cursor::click(bool click, sf::Mouse::Button type) {
    clickFlag = click;
    clickType = type;
}

sf::Mouse::Button Cursor::getClickType() const {
    return clickType;
}

sf::Time Cursor::getClickDuration() const {
    return clickClock.getElapsedTime();
}

bool Cursor::isLongClick() const {
    return getClickDuration().asMilliseconds() > 150;
}

bool Cursor::isMousePressed() const {
    return mousePressedFlag;
}

void Cursor::mousePress(bool mousePressed) {
    mousePressedFlag = mousePressed;
    clickClock.restart();
}

bool Cursor::isMouseReleased() const {
    return mouseReleasedFlag;
}

void Cursor::mouseRelease(bool mouseReleased) {
    mouseReleasedFlag = mouseReleased;
}

void Cursor::resetPressState() {
    mouseReleasedFlag = false;
    mousePressedFlag = false;
}
