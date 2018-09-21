#pragma once

#include "classes/System/Interface/RunnableInterface.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Scene.hpp"

class Editor : public RunnableInterface, public RescalableInterface, public DrawableInterface, public EventReceiverableInterface {

public:

    Editor(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Scale> scale);

    void start() override;
    bool isStarted() override;

    void rescale(sf::Vector2u windowSize) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void handleEvents(Keyboard& keyboard, Cursor& cursor) override;

private:

    bool isStartedFlag = false;
    std::shared_ptr<Navigation> navigation;
    std::shared_ptr<Scene> scene;

    void handleButtonTilesEvents(Keyboard& keyboard, Cursor& cursor);
    void handleSceneTilesEvents(Keyboard& keyboard, Cursor& cursor);

};
