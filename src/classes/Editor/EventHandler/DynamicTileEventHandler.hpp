#pragma once

#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/AbstractTileEventHandler.hpp"
#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Scene.hpp"

class DynamicTileEventHandler: public EventReceiverableInterface, public AbstractTileEventHandler {

public:

    DynamicTileEventHandler(
        std::shared_ptr<EventState> eventState,
        std::shared_ptr<AnimationPerformer> animationPerformer,
        std::shared_ptr<Scene> scene,
        std::shared_ptr<TileFactory> tileFactory,
        std::shared_ptr<TileEventRegistry> tileEventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    void performLongClickDrop(Cursor &cursor);
    void performQuickClickDrop(Cursor &cursor);

    void performHover(Cursor &cursor, std::shared_ptr<DynamicTile> &tile);
    void performDragDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile);
    void performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile);

};
