#pragma once

#include "classes/Editor/EventState.hpp"
#include "classes/Editor/Navigation/TileButton.hpp"
#include "classes/Editor/Scene.hpp"
#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "AbstractTileEventHandler.hpp"

class ButtonTileEventHandler : public EventReceiverableInterface, public AbstractTileEventHandler {

public:

    ButtonTileEventHandler(
        std::unique_ptr<EventState> &eventState,
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory,
        std::unique_ptr<EventRegistry> &tileEventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    void doMouseOver(Cursor &cursor, std::shared_ptr<TileButton> button);
    void doMouseOut(Cursor &cursor, std::shared_ptr<TileButton> button);
    void doMouseClick(Cursor &cursor, std::shared_ptr<TileButton> button);

};
