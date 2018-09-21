#include "EventHandler.hpp"

#include <iostream>
#include "classes/System/Scale.hpp"
#include "classes/Editor/ObjectRegistry.hpp"

EventHandler::EventHandler(Cursor& cursor, std::shared_ptr<Scale> scale) : cursor(cursor) {
    this->scale = scale;
}

sf::Event EventHandler::getLastEvent() {
    return lastEvent;
}

void EventHandler::addEventHandler(EventHandler::Event event, std::function<void()> callback) {
    eventHandlers[event] = callback;
}

void EventHandler::handleEvent(EventHandler::Event event) {
    if (eventHandlers.find(event) == eventHandlers.end()) {
        return;
    }
    eventHandlers[event]();
}

void EventHandler::handleEvents(std::shared_ptr<sf::RenderWindow> window) {
    bool keyChanged = false;

    sf::Event event;
    while (window->pollEvent(event)) {
        lastEvent = event;
        switch (event.type) {
            case sf::Event::Closed: {
                handleEvent(Event::QuitGame);
            } break;
            case sf::Event::KeyPressed: {
                keyChanged = true;
                keyboard.press(event.key.code);
            } break;
            case sf::Event::KeyReleased: {
                keyChanged = true;
                keyboard.release(event.key.code);
            } break;
            case sf::Event::Resized: {
                handleEvent(Event::ResizeWindow);
            } break;
            case sf::Event::MouseButtonPressed: {
                cursor.click(true);
            } break;
            case sf::Event::MouseButtonReleased: {
                cursor.click(false);
            } break;
            case sf::Event::MouseMoved: {
                cursor.handleRegisteredDrags();
            } break;
        }
    }

    if (keyChanged) {
        handleKeyboardEvents();
    }
}

void EventHandler::handleKeyboardEvents() {
    if (keyboard.isPressed(sf::Keyboard::Escape) || keyboard.isPressed(sf::Keyboard::Q)) {
        handleEvent(Event::QuitGame);
        return;
    }

    if (keyboard.isPressed(sf::Keyboard::F)) {
        handleEvent(Event::ToggleFullScreen);
    }
}