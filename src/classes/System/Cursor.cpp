#include "Cursor.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "classes/Editor/ObjectRegistry.hpp"

std::shared_ptr<sf::RenderWindow> Cursor::window;

void Cursor::reinitialize(std::shared_ptr<sf::RenderWindow> &window) {
    Cursor::window = window;
    Cursor::window->setMouseCursorVisible(false);
}

Cursor::Cursor() {
    this->texture = std::make_unique<sf::Texture>();
    this->texture->loadFromFile("resources/cursor.png");

    sprite = std::make_unique<sf::Sprite>(*(texture));

    float scale = 0.15;
    sprite->scale(scale, scale);
    sprite->setPosition(sf::Vector2f(0, 0));
}

void Cursor::updatePosition(sf::Vector2f mousePosition) {
    sprite->setPosition(mousePosition);
}

sf::Vector2f Cursor::getPosition() {
    return sprite->getPosition();
}

void Cursor::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(*sprite);
}

bool Cursor::isMouseMoved() {
    return moveFlag;
}

void Cursor::mouseMove(bool mouseMove) {
    moveFlag = mouseMove;
}

bool Cursor::isOver(sf::Vector2f position, sf::Vector2u size) {
    auto mousePosition = getPosition();
    auto posX = mousePosition.x;
    auto posY = mousePosition.y;

    return posX >= position.x && posY >= position.y &&
           posX <= position.x+size.x &&
           posY <= position.y+size.y;
}

bool Cursor::isClick() {
    return clickFlag;
}

void Cursor::click(bool click, sf::Mouse::Button type) {
    clickFlag = click;
    clickType = type;
}

sf::Mouse::Button Cursor::getClickType() {
    return clickType;
}

sf::Time Cursor::getClickDuration() {
    return clickClock.getElapsedTime();
}

bool Cursor::isLongClick() {
    return getClickDuration().asMilliseconds() > 150;
}

bool Cursor::isMousePressed() {
    return mousePressedFlag;
}

void Cursor::mousePress(bool mousePressed) {
    mousePressedFlag = mousePressed;
    clickClock.restart();
}

bool Cursor::isMouseReleased() {
    return mouseReleasedFlag;
}

void Cursor::mouseRelease(bool mouseReleased) {
    mouseReleasedFlag = mouseReleased;
}

void Cursor::resetPressState() {
    mouseReleasedFlag = false;
    mousePressedFlag = false;
}
