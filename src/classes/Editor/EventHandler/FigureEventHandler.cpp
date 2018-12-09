#include "FigureEventHandler.hpp"

#include <iostream>
#include "classes/Infrastructure/Log.hpp"
#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Scene/Figure.hpp"
#include "classes/Editor/Scene/ResizeIndicator.hpp"
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

void FigureEventHandler::performHover(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    bool isDraggingItem = cursor.draggedItem.has_value();
    auto figurePosition = figure->getPosition();
    auto figureSize = figure->getSize();

    if (cursor.isOver(figurePosition, figureSize) && !eventRegistry->isOverRegistered(figure) && !isDraggingItem) {
        eventRegistry->registerOver(figure);
        figure->mouseEnter(animationPerformer);
    } else if (cursor.isOver(figurePosition, figureSize)) {
        figure->mouseOver(animationPerformer);
        performResizeIndicatorsHover(cursor, figure);
    } else if (eventRegistry->isOverRegistered(figure)) {
        eventRegistry->unregisterOver(figure);
        figure->mouseLeave(animationPerformer);
    }
}

void FigureEventHandler::performResizeIndicatorsHover(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    auto activeResizeIndicators = figure->getActiveResizeIndicators();
    for (auto &indicator : activeResizeIndicators) {
        auto indicatorPosition = indicator->getPosition();
        auto indicatorSize = indicator->getSize();

        bool isOverIndicator = cursor.isOver(indicatorPosition, indicatorSize);
        bool isOverRegistered = eventRegistry->isOverRegistered(indicator);

        if (isOverIndicator && !isOverRegistered) {
            eventRegistry->registerOver(indicator);
            indicator->mouseEnter(animationPerformer);
            continue;
        } else if (!isOverIndicator && isOverRegistered) {
            eventRegistry->unregisterOver(indicator);
            indicator->mouseLeave(animationPerformer);
            continue;
        }
    }
}

void FigureEventHandler::performDragDrop(Cursor& cursor, std::shared_ptr<Figure> &figure) {
    auto figurePosition = figure->getPosition();
    auto figureSize = figure->getSize();

    if (cursor.isOver(figurePosition, figureSize) && eventRegistry->isOverRegistered(figure)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        bool isDraggingItem = cursor.draggedItem.has_value();

        bool isIndicatorClicked = performResizeIndicatorsDragDrop(cursor, figure);
        if (cursor.isClick() && !eventRegistry->isDragRegistered(figure) && isLeftClick && !isDraggingItem) {
            if (!isIndicatorClicked) {
                performStartDragging(cursor, figure);
            }
        } else if (!cursor.isClick() && eventRegistry->isDragRegistered(figure)) {
            performDrop(cursor, figure);
        } else if (!cursor.isClick() && isIndicatorClicked) {
            performResizeIndicatorsDrop(figure);
        }
    } else if (eventRegistry->isOverRegistered(figure) && eventRegistry->isDragRegistered(figure)) {
        performDrop(cursor, figure);
    }
}

void FigureEventHandler::performStartDragging(Cursor &cursor, std::shared_ptr<Figure> &figure) const {
    figure->startDrag(cursor.getPosition(), animationPerformer);
    cursor.draggedItem = figure;
    eventRegistry->registerDrag(figure);
}

bool FigureEventHandler::performResizeIndicatorsDragDrop(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    auto cursorPosition = cursor.getPosition();

    auto activeResizeIndicators = figure->getActiveResizeIndicators();
    for (auto &indicator : activeResizeIndicators) {
        if (eventRegistry->isDragRegistered(indicator)) {
            indicator->drag(cursorPosition);
            return true;
        }

        auto indicatorPosition = indicator->getPosition();
        auto indicatorSize = indicator->getSize();

        bool isOverIndicator = cursor.isOver(indicatorPosition, indicatorSize);
        bool isDragRegistered = eventRegistry->isDragRegistered(indicator);

        if (isOverIndicator) {
            if (!isDragRegistered) {
                eventRegistry->registerDrag(indicator);
                indicator->startDrag(cursorPosition, animationPerformer);
            }
            return true;
        }
    }
    return false;
}

void FigureEventHandler::performResizeIndicatorsDrop(std::shared_ptr<Figure> &figure) {
    auto activeResizeIndicators = figure->getActiveResizeIndicators();
    for (auto &indicator : activeResizeIndicators) {
        if (eventRegistry->isDragRegistered(indicator)) {
            eventRegistry->unregisterDrag(indicator);
            indicator->drop(animationPerformer);
            return;
        }
    }
}

void FigureEventHandler::performDrop(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    eventRegistry->unregisterDrag(figure);
    figure->drop(animationPerformer);
    cursor.draggedItem.reset();
}
