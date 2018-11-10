#include "FigureEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

FigureEventHandler::FigureEventHandler(
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<FigureEventRegistry> &figureEventRegistry
): animationPerformer(animationPerformer), figureEventRegistry(figureEventRegistry) {

}

void FigureEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {

    if (cursor.isMouseMoved()) {
        auto registeredDragOnFigures = figureEventRegistry->getRegisteredDragOnFigures();
        for (auto &dragOnFigure : registeredDragOnFigures) {
            dragOnFigure->drag(cursor.getPosition());
        }
    }

    auto figures = ObjectRegistry::getFigures();
    for (auto &figure : figures) {
        performHover(cursor, figure);
    }

    for (auto &figure : figures) {
        performDragDrop(cursor, figure);
    }
}

void FigureEventHandler::performHover(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    bool isDraggingItem = cursor.draggedItem.has_value();
    auto figurePosition = figure->getPosition();
    auto figureSize = figure->getSize();

    if (cursor.isOver(figurePosition, figureSize) && !figureEventRegistry->isOverRegistered(figure) && !isDraggingItem) {
        figureEventRegistry->registerOver(figure);
        figure->mouseEnter(animationPerformer);
    } else if (cursor.isOver(figurePosition, figureSize)) {
        figure->mouseOver(animationPerformer);
    } else if (figureEventRegistry->isOverRegistered(figure)) {
        figureEventRegistry->unregisterOver(figure);
        figure->mouseLeave(animationPerformer);
    }
}

void FigureEventHandler::performDragDrop(Cursor& cursor, std::shared_ptr<Figure> &figure) {
    auto figurePosition = figure->getPosition();
    auto figureSize = figure->getSize();

    if (cursor.isOver(figurePosition, figureSize) && figureEventRegistry->isOverRegistered(figure)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        bool isDraggingItem = cursor.draggedItem.has_value();
        if (cursor.isClick() && !figureEventRegistry->isDragRegistered(figure) && isLeftClick && !isDraggingItem) {
            figure->startDrag(cursor.getPosition(), animationPerformer);
            cursor.draggedItem = figure;
            figureEventRegistry->registerDrag(figure);
        } else if (!cursor.isClick() && figureEventRegistry->isDragRegistered(figure)) {
            performDrop(cursor, figure);
        }
    } else if (figureEventRegistry->isOverRegistered(figure) && figureEventRegistry->isDragRegistered(figure)) {
        performDrop(cursor, figure);
    }
}

void FigureEventHandler::performDrop(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    figureEventRegistry->unregisterDrag(figure);
    figure->drop(animationPerformer);
    cursor.draggedItem.reset();
}