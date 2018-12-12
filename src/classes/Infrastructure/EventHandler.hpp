#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <SFML/Window/Event.hpp>
#include "classes/Infrastructure/Cursor.hpp"
#include "classes/Infrastructure/Keyboard.hpp"
#include "classes/Infrastructure/Scale.hpp"
#include "classes/Editor/Scene/Tile/DynamicTile.hpp"

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

    explicit EventHandler(Cursor& cursor, std::unique_ptr<Scale> &scale);

    sf::Event getLastEvent() const;
    void addEventHandler(Event event, std::function<void()> callback);
    void handleEvents(std::shared_ptr<sf::RenderWindow> window);

private:

    sf::Event lastEvent;
    std::unique_ptr<Scale> &scale;
    std::map<Event, std::function<void()>> eventHandlers;

    void handleEvent(Event event);
    void handleKeyboardEvents();
};
