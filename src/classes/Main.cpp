#include "Main.hpp"

#include <SFML/Window/Event.hpp>
#include "defines.hpp"
#include "classes/System/Cursor.hpp"

Main::Main() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(windowedWidth, windowedHeight), title, sf::Style::Default
    );

    scale = std::make_shared<Scale>();
    tileFactory = std::make_shared<TileFactory>("resources/tiles.png", scale);
    tilebar = std::make_shared<Tilebar>(tileFactory);
    scene = std::make_shared<Scene>(tileFactory, scale);
    initializeEventHandler();
    reInitializeWindow();
}

void Main::initializeEventHandler() {
    eventHandler = std::make_shared<EventHandler>(cursor, scale);

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
        scale->rescale(window->getSize());
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

void Main::reInitializeWindow() {
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(100);
    window->setKeyRepeatEnabled(false);

    Cursor::reinitialize(window);
    Tile::setWindow(window);

    scale->rescale(window->getSize());
    scene->rescale(window->getSize());
    tilebar->rescale(window->getSize());
}

int Main::run() {
    scene->runTasks();

    while (window->isOpen()) {
        eventHandler->handleSystemEvents(window);
        eventHandler->handleTilesEvents();

        scene->draw(window);
        tilebar->draw(window);
        cursor.draw(window);

        window->display();
    }
    return 0;
}

sf::VideoMode Main::findHighestResolutionMode() {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (auto mode : modes) {
        if (mode.height > maxHeightMode.height) {
            maxHeightMode = mode;
        }
    }
    return maxHeightMode;
}
