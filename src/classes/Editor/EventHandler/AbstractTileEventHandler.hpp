#pragma once

#include "classes/Infrastructure/Cursor.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/EventState.hpp"
#include "classes/Editor/EventHandler/EventRegistry.hpp"

class AbstractTileEventHandler {

public:

    AbstractTileEventHandler(
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

    void createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<ButtonTile> button);
    void cancelDragging(Cursor& cursor);

};
