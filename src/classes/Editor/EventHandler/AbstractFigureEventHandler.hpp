#pragma once

#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/EventHandler/EventRegistry.hpp"

class AbstractFigureEventHandler {

public:

    AbstractFigureEventHandler(
        std::unique_ptr<EventState> &eventState,
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory,
        std::unique_ptr<EventRegistry> &eventRegistry
    );

protected:

    std::unique_ptr<EventState> &eventState;
    std::unique_ptr<AnimationPerformer> &animationPerformer;
    std::unique_ptr<Scene> &scene;
    std::unique_ptr<TileFactory> &tileFactory;
    std::unique_ptr<EventRegistry> &eventRegistry;

};
