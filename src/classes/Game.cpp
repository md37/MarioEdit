#include "Game.hpp"

#include <SFML/Window/Event.hpp>
#include "defines.hpp"
#include "classes/Cursor.hpp"
#include "classes/Scale.hpp"
#include "classes/Tile/TileFactory.hpp"
#include "classes/Tile/TileRegistry.hpp"
#include "classes/Animation/FrameAnimation/Animation/SpecialBlockBlinkingAnimation.hpp"

Game::Game() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(windowedWidth, windowedHeight), title, sf::Style::Default
    );

    grid = std::make_shared<Grid>(window->getSize());
    tileSet = std::make_shared<TileFactory>("resources/tiles.png");
    tileSet->setTileSeparators(1, 1);
    tileSet2 = std::make_shared<TileFactory>("resources/tiles2.png");

    initializeEventHandler();
    reinitializeWindow();
}

void Game::initializeEventHandler() {
    eventHandler = std::make_shared<EventHandler>(cursor);

    eventHandler->addEventHandler(EventHandler::QuitGame, [=]() {
        window->close();
    });

    eventHandler->addEventHandler(EventHandler::ResizeWindow, [=]() {
        sf::Event event = eventHandler->getLastEvent();

        width = event.size.width;
        height = event.size.height;
        windowedWidth = event.size.width;
        windowedHeight = event.size.height;

        if (event.size.height < minWindowHeight) {
            window->setSize(sf::Vector2u(event.size.width, minWindowHeight));
            height = minWindowHeight;
            windowedHeight = minWindowHeight;
        }

        sf::Vector2u newSize(width, height);
        Scale::rescale(newSize);
        grid->rescale(newSize);
        resnapTilesToGrid();
        window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
    });

    eventHandler->addEventHandler(EventHandler::ToggleFullScreen, [=]() {
        isFullscreen = !isFullscreen;

        if (isFullscreen) {
            sf::VideoMode mode = findHighestResolutionMode();
            width = mode.width;
            height = mode.height;
            window->create(mode, title, isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        } else {
            width = windowedWidth;
            height = windowedHeight;

            sf::VideoMode mode(width, height);
            window->create(mode, title, isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        }
        reinitializeWindow();
    });
}

void Game::reinitializeWindow() {
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(100);
    window->setKeyRepeatEnabled(false);

    Tile::setWindow(window);
    Scale::rescale(window->getSize());
    Cursor::reinitialize(window);

    grid->rescale(window->getSize());
    resnapTilesToGrid();
}

int Game::run() {
    createTiles();

    auto dynamicTiles = TileRegistry::getDynamicTiles();
    
    SpecialBlockBlinkingAnimation blinkAnimation(dynamicTiles);
    blinkAnimation.run();

    while (window->isOpen()) {
        eventHandler->handleSystemEvents(window);
        eventHandler->handleDynamicTilesEvents(dynamicTiles);

        window->clear(BG_LIGHT_COLOR);
        grid->draw(window);

        for (std::size_t i=0; i<dynamicTiles.size(); i++) {
            dynamicTiles[i]->draw(window);
        }

        cursor.draw();
        window->display();
    }
    return 0;
}

void Game::createTiles() {
    auto questionMark = tileSet2->createDynamicTile(0, 5);
    questionMark->addEventHandler(DynamicTile::MouseEnter, [](DynamicTile *tile) {
        tile->highlight();
    });
    questionMark->addEventHandler(DynamicTile::MouseLeave, [](DynamicTile *tile) {
        tile->undoHighlight();
    });
    questionMark->addEventHandler(DynamicTile::StartDrag, [](DynamicTile *tile) {
        tile->changeImage(0, 5);
        tile->startDrag();
    });
    questionMark->addEventHandler(DynamicTile::Drag, [](DynamicTile *tile) {
        tile->drag();
    });
    questionMark->addEventHandler(DynamicTile::Drop, [](DynamicTile *tile) {
        tile->drop();
    });

    questionMark->setGrid(grid);
    questionMark->snapToGrid(sf::Vector2u(2, 1));
}

void Game::resnapTilesToGrid() {
    auto tiles = TileRegistry::getDynamicTiles();
    for (size_t i=0; i < tiles.size(); i++) {
        auto tile = tiles[i];
        tile->snapToGrid();
    }
}

sf::VideoMode Game::findHighestResolutionMode() {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (int i=0; i<modes.size(); i++) {
        if (modes[i].height > maxHeightMode.height) {
            maxHeightMode = modes[i];
        }
    }
    return maxHeightMode;
}
