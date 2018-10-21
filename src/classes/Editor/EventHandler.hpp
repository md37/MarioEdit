#pragma once

#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/ButtonTileEventHandler.hpp"
#include "classes/Editor/EventHandler/DynamicTileEventHandler.hpp"

class EditorEventHandler : public EventReceiverableInterface {

public:

    EditorEventHandler(
        std::shared_ptr<AnimationPerformer> animationPerformer,
        std::shared_ptr<Scene> scene,
        std::shared_ptr<TileFactory> tileFactory
    );

    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    std::shared_ptr<EventState> currentState;

    std::shared_ptr<ButtonTileEventHandler> buttonTileEventHandler;
    std::shared_ptr<DynamicTileEventHandler> dynamicTileEventHandler;
};
