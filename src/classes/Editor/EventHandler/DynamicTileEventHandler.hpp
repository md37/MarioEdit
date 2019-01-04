#pragma once

#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/AbstractTileEventHandler.hpp"
#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Scene.hpp"

class DynamicTileEventHandler: public EventReceiverableInterface, public AbstractTileEventHandler {

public:

    DynamicTileEventHandler(
        std::unique_ptr<EventState> &eventState,
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory,
        std::unique_ptr<EventRegistry> &eventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    void performLongClickDrop(Cursor &cursor);
    void performQuickClickDrop(Cursor &cursor);

    void performHover(Cursor &cursor, std::shared_ptr<DynamicTile> tile);
    void performDragDrop(Cursor &cursor, std::shared_ptr<DynamicTile> tile);
    void performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> tile);

};
