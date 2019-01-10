#include "Main.hpp"

#include <SFML/Window/Event.hpp>
#include "classes/Infrastructure/Cursor.hpp"

Main::Main() {
    window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(windowedWidth, windowedHeight), title, sf::Style::Titlebar | sf::Style::Close
    );

    scale = std::make_unique<Scale>(window->getSize());
    tileFactory = std::make_unique<TileFactory>("resources/tiles.png", scale);
    editor = std::make_unique<Editor>(tileFactory);
    game = std::make_unique<Game>();

    initializeEventHandler();
    reInitializeWindow();
}

void Main::initializeEventHandler() {
    systemEventHandler = std::make_unique<EventHandler>(cursor, scale);

    systemEventHandler->addEventHandler(EventHandler::QuitGame, [=]() {
        window->close();
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
            window->create(mode, title, sf::Style::Titlebar | sf::Style::Close);
        }

        reInitializeWindow();
    });
}

void Main::reInitializeWindow() {
    sf::Image iconImage;
    iconImage.loadFromFile("resources/icon.png");
    window->setIcon(710, 710, iconImage.getPixelsPtr());

    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(100);
    window->setKeyRepeatEnabled(false);

    Cursor::reinitialize(window);
    AbstractTile::setWindow(window);

    scale->change(window->getSize());
    editor->rescale(scale);
}

int Main::run() {
    editor->start();

    while (window->isOpen()) {
        systemEventHandler->handleEvents(window);

        if (editor->isStarted()) {
            editor->runAnimations();

            editor->handleEvents(systemEventHandler->keyboard, systemEventHandler->cursor);
            editor->draw(window);
        }

        cursor.draw(window);
        window->display();
    }
    return 0;
}