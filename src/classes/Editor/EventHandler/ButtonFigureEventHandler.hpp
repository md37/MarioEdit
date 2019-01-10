#pragma once

#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/AbstractFigureEventHandler.hpp"
#include "classes/Editor/Navigation/FigureButton.hpp"

class ButtonFigureEventHandler: public EventReceiverableInterface, AbstractFigureEventHandler {

public:

    ButtonFigureEventHandler(
        std::unique_ptr<EventState> &eventState,
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory,
        std::unique_ptr<EventRegistry> &tileEventRegistry
    );

    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    void doMouseOver(Cursor &cursor, std::shared_ptr<FigureButton> button);
    void doMouseOut(Cursor &cursor, std::shared_ptr<FigureButton> button);
    void doMouseClick(Cursor &cursor, std::shared_ptr<FigureButton> button);

    void createFigureSnappedToCursor(Cursor &cursor, std::shared_ptr<FigureButton> button);
    void cancelDragging(Cursor &cursor);

};
