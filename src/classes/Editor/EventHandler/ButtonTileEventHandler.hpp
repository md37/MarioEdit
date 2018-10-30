#pragma once

#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "AbstractTileEventHandler.hpp"

class ButtonTileEventHandler : public EventReceiverableInterface, public AbstractTileEventHandler {

public:

    ButtonTileEventHandler(
        std::shared_ptr<EventState> eventState,
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory,
        std::shared_ptr<TileEventRegistry> tileEventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    void doMouseOver(Cursor &cursor, std::shared_ptr<ButtonTile> button);
    void doMouseOut(Cursor &cursor, std::shared_ptr<ButtonTile> button);
    void doMouseClick(Cursor &cursor, std::shared_ptr<ButtonTile> button);

};
