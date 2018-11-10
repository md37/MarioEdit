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

bool Cursor::isOver(std::shared_ptr<Tile> tile) {
    auto mousePosition = getPosition();
    float posX = mousePosition.x;
    float posY = mousePosition.y;

    return posX >= tile->getPosition().x && posY >= tile->getPosition().y &&
           posX <= tile->getPosition().x+tile->getSize().x &&
           posY <= tile->getPosition().y+tile->getSize().y;
}

bool Cursor::isOver(std::shared_ptr<Figure> figure) {
    auto mousePosition = getPosition();
    float posX = mousePosition.x;
    float posY = mousePosition.y;

    return posX >= figure->getPosition().x && posY >= figure->getPosition().y &&
           posX <= figure->getPosition().x+figure->getSize().x &&
           posY <= figure->getPosition().y+figure->getSize().y;
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

sf::Time Cursor::getClickDuration() {
    return clickClock.getElapsedTime();
}

bool Cursor::isLongClick() {
    return getClickDuration().asMilliseconds() > 150;
}
