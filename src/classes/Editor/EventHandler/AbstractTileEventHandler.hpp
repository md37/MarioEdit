#pragma once

#include "classes/System/Cursor.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Editor/EventState.hpp"

class AbstractTileEventHandler {

public:

    AbstractTileEventHandler(
        std::shared_ptr<EventState> eventState,
        std::shared_ptr<AnimationPerformer> animationPerformer,
        std::shared_ptr<Scene> scene,
        std::shared_ptr<TileFactory> tileFactory
    );

protected:

    std::shared_ptr<EventState> eventState;
    std::shared_ptr<AnimationPerformer> animationPerformer;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<TileFactory> tileFactory;

    void createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<ButtonTile> button);
    void cancelDragging(Cursor& cursor);

};
