#include "Game.hpp"

#include <SFML/Window/Event.hpp>
#include "defines.hpp"
#include "classes/Cursor.hpp"

Game::Game() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(windowedWidth, windowedHeight), title, sf::Style::Default
    );

    scene = std::make_shared<Scene>(window);
    tilebar = std::make_shared<Tilebar>(window);
    initializeEventHandler();
    reInitializeWindow();
}

void Game::initializeEventHandler() {
    eventHandler = std::make_shared<EventHandler>(cursor, scene->getScale());

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

        window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
        scene->rescale(window->getSize());
        tilebar->rescale(window->getSize());
    });

    eventHandler->addEventHandler(EventHandler::ToggleFullScreen, [=]() {
        isFullscreen = !isFullscreen;

        if (isFullscreen) {
            sf::VideoMode mode = findHighestResolutionMode();
            width = mode.width;
            height = mode.height;
            window->create(mode, title, sf::Style::Fullscreen);
        } else {
            width = windowedWidth;
            height = windowedHeight;

            sf::VideoMode mode(width, height);
            window->create(mode, title, sf::Style::Default);
        }
        reInitializeWindow();
    });
}

void Game::reInitializeWindow() {
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(100);
    window->setKeyRepeatEnabled(false);

    Cursor::reinitialize(window);

    scene->rescale(window->getSize());
    tilebar->rescale(window->getSize());
}

int Game::run() {
    scene->runTasks();

    while (window->isOpen()) {
        eventHandler->handleSystemEvents(window);
        eventHandler->handleDynamicTilesEvents();

        scene->draw(window);
        tilebar->draw(window);
        cursor.draw(window);

        window->display();
    }
    return 0;
}

sf::VideoMode Game::findHighestResolutionMode() {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (auto mode : modes) {
        if (mode.height > maxHeightMode.height) {
            maxHeightMode = mode;
        }
    }
    return maxHeightMode;
}
