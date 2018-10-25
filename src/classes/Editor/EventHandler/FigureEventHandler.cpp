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

    for (auto &figure : figures) {
        performDragDrop(cursor, figure);
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

void FigureEventHandler::performDragDrop(Cursor& cursor, std::shared_ptr<Figure> &figure) {
    if (cursor.isOver(figure) && figureEventRegistry->isOverRegistered(figure)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        if (cursor.isClick() && !figureEventRegistry->isDragRegistered(figure) && isLeftClick) {
            figure->startDrag(animationPerformer);
            figureEventRegistry->registerDrag(figure);
        } else if (!cursor.isClick() && figureEventRegistry->isDragRegistered(figure)) {
            performDrop(cursor, figure);
        }
    } else if (figureEventRegistry->isOverRegistered(figure) && figureEventRegistry->isDragRegistered(figure)) {
        performDrop(cursor, figure);
    }
}

void FigureEventHandler::performDrop(Cursor &cursor, std::shared_ptr<Figure> &figure) {
//    auto dropHighlightPlace = scene->getGrid()->getHighlightPlace();

    figureEventRegistry->unregisterDrag(figure);
    figure->drop(animationPerformer);
}