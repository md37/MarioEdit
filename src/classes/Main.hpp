#pragma once

#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/Editor/Scene.hpp"
#include "classes/System/EventHandler.hpp"
#include "classes/System/Cursor.hpp"

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

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<EventHandler> eventHandler;

    std::shared_ptr<Scale> scale;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Tilebar> tilebar;
    std::shared_ptr<Scene> scene;

    Cursor cursor;

    void initializeEventHandler();

    void reInitializeWindow();
    sf::VideoMode findHighestResolutionMode();
};