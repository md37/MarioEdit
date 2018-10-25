#pragma once

#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/Scene/Figure.hpp"
#include "classes/Editor/EventHandler/CursorEventRegistry/FigureRegistry.hpp"

class FigureEventHandler : public EventReceiverableInterface {

public:

    FigureEventHandler(
        std::shared_ptr<AnimationPerformer> animationPerformer,
        std::shared_ptr<FigureEventRegistry> figureEventRegistry
    );
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    std::shared_ptr<AnimationPerformer> animationPerformer;
    std::shared_ptr<FigureEventRegistry> figureEventRegistry;
    void performHover(Cursor &cursor, std::shared_ptr<Figure> &figure);
    void performDragDrop(Cursor &cursor, std::shared_ptr<Figure> &figure);
    void performDrop(Cursor &cursor, std::shared_ptr<Figure> &figure);
};
