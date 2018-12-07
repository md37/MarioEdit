#pragma once

#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/EventHandler/EventRegistry.hpp"

class Figure;

class FigureEventHandler : public EventReceiverableInterface {

public:

    FigureEventHandler(
        std::unique_ptr<AnimationPerformer> &animationPerformer,
        std::unique_ptr<EventRegistry> &figureEventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    std::unique_ptr<AnimationPerformer> &animationPerformer;
    std::unique_ptr<EventRegistry> &figureEventRegistry;

    void performHover(Cursor &cursor, std::shared_ptr<Figure> &figure);
    void performDragDrop(Cursor &cursor, std::shared_ptr<Figure> &figure);
    void performDrop(Cursor &cursor, std::shared_ptr<Figure> &figure);
};
