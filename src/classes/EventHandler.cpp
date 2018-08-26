#include "EventHandler.hpp"

#include "classes/Scale.hpp"
#include "classes/Tile/TileRegistry.hpp"

EventHandler::EventHandler(Cursor& cursor) : cursor(cursor) {

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

void EventHandler::handleSystemEvents(std::shared_ptr<sf::RenderWindow> window) {
    bool keyChanged = false;

    sf::Event event;
    while (window->pollEvent(event)) {
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

void EventHandler::handleDynamicTilesEvents() {
    auto tiles = TileRegistry::getDynamicTiles();

    for (size_t i=0; i < tiles.size(); i++) {
        auto tile = tiles[i];
        if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
            cursor.registerOver(tile);
            tile->handleEvent(DynamicTile::MouseEnter);
        } else if (cursor.isOver(tile)) {
            tile->handleEvent(DynamicTile::MouseOver);

            if (cursor.isClick() && !cursor.isDragRegistered(tile)) {
                cursor.registerDrag(tile);
                tile->handleEvent(DynamicTile::StartDrag);
            } else if (!cursor.isClick() && cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->handleEvent(DynamicTile::Drop);
            }
        } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
            if (cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->handleEvent(DynamicTile::Drop);
            }
            cursor.unregisterOver(tile);
            tile->handleEvent(DynamicTile::MouseLeave);
        } else {
            if (cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->handleEvent(DynamicTile::Drop);
            }
        }
        tile->rescale(Scale::getScale());
    }
}

sf::Event EventHandler::getLastEvent() {
    return lastEvent;
}