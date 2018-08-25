#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <SFML/Window/Event.hpp>
#include "classes/Cursor.hpp"
#include "classes/Keyboard.hpp"
#include "classes/Tile/DynamicTile.hpp"

class Game;

class EventHandler {

public:

    enum Event {
        QuitGame,
        ToggleFullScreen,
        ResizeWindow,
    };

    explicit EventHandler(Cursor& cursor);

    sf::Event getLastEvent();
    void addEventHandler(Event event, std::function<void()> callback);
    void handleSystemEvents(std::shared_ptr<sf::RenderWindow> window);
    void handleDynamicTilesEvents(const std::vector<std::shared_ptr<DynamicTile>> &tiles);

private:

    Cursor& cursor;
    Keyboard keyboard;
    sf::Event lastEvent;
    std::map<Event, std::function<void()>> eventHandlers;

    void handleEvent(Event event);
    void handleKeyboardEvents();


};
