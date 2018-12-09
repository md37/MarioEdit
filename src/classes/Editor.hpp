#pragma once

#include <memory>
#include "classes/Infrastructure/Interface/RunnableInterface.hpp"
#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/EventHandler.hpp"

class Editor : public RunnableInterface, public RescalableInterface, public DrawableInterface, public EventReceiverableInterface {

public:

    explicit Editor(std::unique_ptr<TileFactory> &tileFactory);

    void start() override;
    bool isStarted() override;

    void rescale(std::unique_ptr<Scale>& scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) const override;

    void handleEvents(Keyboard& keyboard, Cursor& cursor) override;
    void runAnimations();

private:

    bool isStartedFlag = false;
    std::unique_ptr<TileFactory> &tileFactory;
    std::unique_ptr<Navigation> navigation;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<AnimationPerformer> animationPerformer;

    std::unique_ptr<EditorEventHandler> eventHandler;
};
