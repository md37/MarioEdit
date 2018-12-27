#pragma once

#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/EventRegistry.hpp"

class DynamicFigure;

class FigureEventHandler : public EventReceiverableInterface {

public:

    FigureEventHandler(
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<EventRegistry> &figureEventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    std::unique_ptr<AnimationPerformer> &animationPerformer;
    std::unique_ptr<EventRegistry> &eventRegistry;

    void performHover(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure);

    void performDragDrop(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure);
    void performStartDragging(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure);
    void performDrop(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure);
};
