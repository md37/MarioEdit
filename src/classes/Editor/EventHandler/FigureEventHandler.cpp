#include "FigureEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

FigureEventHandler::FigureEventHandler(
    std::shared_ptr<AnimationPerformer> animationPerformer,
    std::shared_ptr<FigureEventRegistry> figureEventRegistry
) {
    this->animationPerformer = animationPerformer;
    this->figureEventRegistry = figureEventRegistry;
}

void FigureEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    auto figures = ObjectRegistry::getFigures();

    for (auto &figure : figures) {
        performHover(cursor, figure);
    }
}

void FigureEventHandler::performHover(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    if (cursor.isOver(figure) && !figureEventRegistry->isOverRegistered(figure)) {
        figureEventRegistry->registerOver(figure);
        figure->mouseEnter(animationPerformer);
    } else if (cursor.isOver(figure)) {
        figure->mouseOver(animationPerformer);
    } else if (figureEventRegistry->isOverRegistered(figure)) {
        figureEventRegistry->unregisterOver(figure);
        figure->mouseLeave(animationPerformer);
    }
}
