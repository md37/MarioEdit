#include "Main.hpp"

#include <SFML/Window/Event.hpp>
#include "classes/System/Cursor.hpp"

Main::Main() {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(windowedWidth, windowedHeight), title, sf::Style::Default
    );

    scale = std::make_shared<Scale>();
    tileFactory = std::make_shared<TileFactory>("resources/tiles.png", scale);
    editor = std::make_shared<Editor>(tileFactory, scale);
    game = std::make_shared<Game>();

    initializeEventHandler();
    reInitializeWindow();
}

void Main::initializeEventHandler() {
    systemEventHandler = std::make_shared<EventHandler>(cursor, scale);

    systemEventHandler->addEventHandler(EventHandler::QuitGame, [=]() {
        window->close();
    });

    systemEventHandler->addEventHandler(EventHandler::ResizeWindow, [=]() {
        sf::Event event = systemEventHandler->getLastEvent();

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
        editor->rescale(window->getSize());
    });

    systemEventHandler->addEventHandler(EventHandler::ToggleFullScreen, [=]() {
        isFullscreen = !isFullscreen;

        if (isFullscreen) {
            sf::VideoMode mode = resolution.findHighestResolutionMode();
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
    editor->rescale(window->getSize());
}

int Main::run() {
    editor->start();

    while (window->isOpen()) {
        systemEventHandler->handleEvents(window);

        if (editor->isStarted()) {
            editor->handleEvents(systemEventHandler->keyboard, systemEventHandler->cursor);
        }

        editor->draw(window);
        cursor.draw(window);

        window->display();
    }
    return 0;
}