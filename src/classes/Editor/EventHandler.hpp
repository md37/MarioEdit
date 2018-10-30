#pragma once

#include "classes/Editor/EventHandler/CursorEventRegistry/TileRegistry.hpp"
#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"
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

    std::shared_ptr<EventState> currentState;

    std::shared_ptr<ButtonTileEventHandler> buttonTileEventHandler;
    std::shared_ptr<DynamicTileEventHandler> dynamicTileEventHandler;
    std::shared_ptr<FigureEventHandler> figureEventHandler;

    std::shared_ptr<TileEventRegistry> tileEventRegistry;
    std::shared_ptr<FigureEventRegistry> figureEventRegistry;
};
