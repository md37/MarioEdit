#pragma once

#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/EventRegistry.hpp"
#include "classes/Editor/EventHandler/AbstractFigureEventHandler.hpp"

class DynamicFigure;

class FigureEventHandler : public EventReceiverableInterface, AbstractFigureEventHandler {

public:

    FigureEventHandler(
        std::unique_ptr<EventState> &eventState,
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<Scene> &scene,
        std::unique_ptr<TileFactory> &tileFactory,
        std::unique_ptr<EventRegistry> &eventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    void performHover(Cursor &cursor, std::shared_ptr<DynamicFigure> figure);

    void performDragDrop(Cursor &cursor, std::shared_ptr<DynamicFigure> figure);
    void performStartDragging(Cursor &cursor, std::shared_ptr<DynamicFigure> figure);
    void performDrop(Cursor &cursor, std::shared_ptr<DynamicFigure> figure);

};
