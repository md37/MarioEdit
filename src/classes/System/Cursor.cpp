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
    this->texture = std::make_shared<sf::Texture>();
    this->texture->loadFromFile("resources/cursor.png");

    sprite = std::make_shared<sf::Sprite>(*(texture));

    float scale = 0.15;
    sprite->scale(scale, scale);
}

void Cursor::updatePosition() {
    auto mousePosition = Cursor::getCurrentPosition();
    sprite->setPosition(mousePosition.x, mousePosition.y);
}

sf::Vector2f Cursor::getCurrentPosition() {
    return sf::Vector2f(sf::Mouse::getPosition(*(window)));
}

void Cursor::draw(std::shared_ptr<sf::RenderWindow> window) {
    updatePosition();
    window->draw(*sprite);
}

bool Cursor::isMouseMoved() {
    return moveFlag;
}

void Cursor::mouseMove(bool mouseMove) {
    moveFlag = mouseMove;
}

bool Cursor::isOver(std::shared_ptr<Tile> tile) {
    auto mousePosition = sf::Mouse::getPosition(*(Cursor::window));
    int posX = mousePosition.x;
    int posY = mousePosition.y;

    return posX >= tile->getPosition().x && posY >= tile->getPosition().y &&
           posX <= tile->getPosition().x+tile->getSize().x &&
           posY <= tile->getPosition().y+tile->getSize().y;
}

bool Cursor::isOver(std::shared_ptr<Figure> figure) {
    auto mousePosition = sf::Mouse::getPosition(*(Cursor::window));
    int posX = mousePosition.x;
    int posY = mousePosition.y;

    return posX >= figure->getPosition().x && posY >= figure->getPosition().y &&
           posX <= figure->getPosition().x+figure->getSize().x &&
           posY <= figure->getPosition().y+figure->getSize().y;
}

bool Cursor::isClickOn(std::shared_ptr<Tile> tile) {
    return this->isOver(tile) && this->isClick();
}

bool Cursor::isClickOn(std::shared_ptr<Figure> figure) {
    return this->isOver(figure) && this->isClick();
}

bool Cursor::isClick() {
    return clickFlag;
}

void Cursor::click(bool click, sf::Mouse::Button type) {
    clickFlag = click;
    clickType = type;
}

sf::Time Cursor::getClickDuration() {
    return clickClock.getElapsedTime();
}

void Cursor::resetPressState() {
    mouseReleasedFlag = false;
    mousePressedFlag = false;
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

bool Cursor::isLongClick() {
    return getClickDuration().asMilliseconds() > 150;
}

sf::Mouse::Button Cursor::getClickType() {
    return clickType;
}
