#pragma once

#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "classes/EventHandler.hpp"
#include "classes/Keyboard.hpp"
#include "classes/Scale.hpp"
#include "classes/Cursor.hpp"
#include "classes/Grid.hpp"
#include "classes/Tile/TileFactory.hpp"

class Game {

public:

    Game();

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

    Cursor cursor;
    std::shared_ptr<TileFactory> tileSet;
    std::shared_ptr<TileFactory> tileSet2;
    std::shared_ptr<Grid> grid;

    void initializeEventHandler();

    void createTiles();
    void resnapTilesToGrid();

    void reinitializeWindow();
    sf::VideoMode findHighestResolutionMode();
};