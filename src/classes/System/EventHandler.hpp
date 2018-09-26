#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <SFML/Window/Event.hpp>
#include "classes/System/Cursor.hpp"
#include "classes/System/Keyboard.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"
#include "classes/System/Scale.hpp"

class Main;

class EventHandler {

public:

    enum Event {
        QuitGame,
        ToggleFullScreen,
        ResizeWindow,
    };

    Cursor& cursor;
    Keyboard keyboard;

    explicit EventHandler(Cursor& cursor, std::shared_ptr<Scale> scale);

    sf::Event getLastEvent();
    void addEventHandler(Event event, std::function<void()> callback);
    void handleEvents(std::shared_ptr<sf::RenderWindow> window);

private:

    sf::Event lastEvent;
    std::shared_ptr<Scale> scale;
    std::map<Event, std::function<void()>> eventHandlers;

    void handleEvent(Event event);
    void handleKeyboardEvents();
};
