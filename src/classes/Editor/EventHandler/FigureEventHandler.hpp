#pragma once

#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/Scene/Figure.hpp"

class FigureEventHandler : public EventReceiverableInterface {

public:

    FigureEventHandler(std::shared_ptr<AnimationPerformer> animationPerformer);
    void handleEvents(Keyboard &keyboard, Cursor &cursor) override;

private:

    std::shared_ptr<AnimationPerformer> animationPerformer;
    void performHover(Cursor &cursor, std::shared_ptr<Figure> &figure);
};
