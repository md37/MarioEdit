#include "FigureEventHandler.hpp"

#include "classes/Infrastructure/Log.hpp"
#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"
#include "classes/Editor/EventHandler/DragVisitator.hpp"

FigureEventHandler::FigureEventHandler(
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<EventRegistry> &figureEventRegistry
): animationPerformer(animationPerformer), eventRegistry(figureEventRegistry) {

}

void FigureEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    if (cursor.isMouseMoved()) {
        auto registeredDragOnFigures = eventRegistry->getRegisteredDrags();
        for (auto &dragOnItem : registeredDragOnFigures) {
            std::visit(DragVisitator(cursor), dragOnItem);
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

void FigureEventHandler::performHover(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure) {
    bool isDraggingItem = cursor.draggedItem.has_value();
    auto figurePosition = figure->getPosition();
    auto figureSize = figure->getSize();

    if (cursor.isOver(figurePosition, figureSize) && !eventRegistry->isOverRegistered(figure) && !isDraggingItem) {
        eventRegistry->registerOver(figure);
        figure->mouseEnter(animationPerformer);
    } else if (cursor.isOver(figurePosition, figureSize)) {
        figure->mouseOver(animationPerformer);
    } else if (eventRegistry->isOverRegistered(figure)) {
        eventRegistry->unregisterOver(figure);
        figure->mouseLeave(animationPerformer);
    }
}

void FigureEventHandler::performDragDrop(Cursor& cursor, std::shared_ptr<DynamicFigure> &figure) {
    auto figurePosition = figure->getPosition();
    auto figureSize = figure->getSize();

    if (cursor.isOver(figurePosition, figureSize) && eventRegistry->isOverRegistered(figure)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        bool isDraggingItem = cursor.draggedItem.has_value();

        if (cursor.isClick() && !eventRegistry->isDragRegistered(figure) && isLeftClick && !isDraggingItem) {
            performStartDragging(cursor, figure);
        } else if (!cursor.isClick() && eventRegistry->isDragRegistered(figure)) {
            performDrop(cursor, figure);
        }
    } else if (eventRegistry->isOverRegistered(figure) && eventRegistry->isDragRegistered(figure)) {
        performDrop(cursor, figure);
    }
}

void FigureEventHandler::performStartDragging(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure) {
    figure->startDrag(cursor.getPosition(), animationPerformer);
    cursor.draggedItem = figure;
    eventRegistry->registerDrag(figure);
}

void FigureEventHandler::performDrop(Cursor &cursor, std::shared_ptr<DynamicFigure> &figure) {
    eventRegistry->unregisterDrag(figure);
    figure->drop(animationPerformer);
    cursor.draggedItem.reset();
}
