#pragma once

#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Scene.hpp"
#include "classes/System/EventHandler.hpp"
#include "classes/System/Cursor.hpp"
#include "classes/System/Resolution.hpp"
#include "classes/Editor.hpp"
#include "classes/Game.hpp"

class Main {

public:

    Main();

    int run();

private:

    const std::string title = "Mario::Edit";
    sf::Uint32 minWindowHeight = 640;
    sf::Uint32 width = 1280;
    sf::Uint32 height = 960;
    sf::Uint32 windowedWidth = 1280;
    sf::Uint32 windowedHeight = 960;
    bool isFullscreen = false;

    Resolution resolution;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<EventHandler> systemEventHandler;

    std::shared_ptr<Scale> scale;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Editor> editor;
    std::shared_ptr<Game> game;

    Cursor cursor;

    void initializeEventHandler();

    void reInitializeWindow();
};