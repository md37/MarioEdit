#pragma once

#include "classes/System/Interface/RunnableInterface.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/EventHandler.hpp"

class Editor : public RunnableInterface, public RescalableInterface, public DrawableInterface, public EventReceiverableInterface {

public:

    explicit Editor(std::shared_ptr<TileFactory> tileFactory);

    void start() override;
    bool isStarted() override;

    void rescale(std::shared_ptr<Scale> scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void handleEvents(Keyboard& keyboard, Cursor& cursor) override;
    void runAnimations();

private:

    bool isStartedFlag = false;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Navigation> navigation;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<AnimationPerformer> animationPerformer;

    std::shared_ptr<EditorEventHandler> eventHandler;
};
