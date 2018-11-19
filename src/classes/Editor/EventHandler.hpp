#pragma once

#include "classes/Editor/EventHandler/EventRegistry.hpp"
#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/ButtonTileEventHandler.hpp"
#include "classes/Editor/EventHandler/DynamicTileEventHandler.hpp"
#include "classes/Editor/EventHandler/FigureEventHandler.hpp"

class EditorEventHandler : public EventReceiverableInterface {

public:

    EditorEventHandler(
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory
    );

    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    std::unique_ptr<EventState> currentState;

    std::unique_ptr<ButtonTileEventHandler> buttonTileEventHandler;
    std::unique_ptr<DynamicTileEventHandler> dynamicTileEventHandler;
    std::unique_ptr<FigureEventHandler> figureEventHandler;

    std::unique_ptr<EventRegistry> eventRegistry;
};
