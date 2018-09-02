#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <SFML/Window/Event.hpp>
#include "classes/Cursor.hpp"
#include "classes/Keyboard.hpp"
#include "classes/Scene/Tile/DynamicTile.hpp"
#include "classes/Scene/Scale.hpp"

class Game;

class EventHandler {

public:

    enum Event {
        QuitGame,
        ToggleFullScreen,
        ResizeWindow,
    };

    explicit EventHandler(Cursor& cursor, std::shared_ptr<Scale> scale);

    sf::Event getLastEvent();
    void addEventHandler(Event event, std::function<void()> callback);
    void handleSystemEvents(std::shared_ptr<sf::RenderWindow> window);
    void handleDynamicTilesEvents();

private:

    Cursor& cursor;
    Keyboard keyboard;
    sf::Event lastEvent;
    std::shared_ptr<Scale> scale;
    std::map<Event, std::function<void()>> eventHandlers;

    void handleEvent(Event event);
    void handleKeyboardEvents();


};
