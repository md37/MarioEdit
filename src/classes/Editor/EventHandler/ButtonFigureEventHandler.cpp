#include "ButtonFigureEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

ButtonFigureEventHandler::ButtonFigureEventHandler(
    std::unique_ptr<EventState> &eventState,
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory,
    std::unique_ptr<EventRegistry> &tileEventRegistry
): AbstractFigureEventHandler(eventState, animationPerformer, scene, tileFactory, tileEventRegistry){

}

void ButtonFigureEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    auto buttons = ObjectRegistry::getButtonFigures();

    if (!eventState->isDraggingNewObject) {
        for (auto &button: buttons) {
            auto buttonPosition = button->getPosition();
            auto buttonSize = button->getSize();
            if (cursor.isOver(buttonPosition, buttonSize)) {
                doMouseOver(cursor, button);

                if (cursor.isMousePressed()) {
                    doMouseClick(cursor, button);
                }
                break;
            } else if (eventRegistry->isOverRegistered(button)) {
                doMouseOut(cursor, button);
                break;
            }
        }
        return;
    }

    for (auto &button: buttons) {
        auto buttonPosition = button->getPosition();
        auto buttonSize = button->getSize();
        if (cursor.isOver(buttonPosition, buttonSize) && cursor.isMouseReleased()) {
            eventState->dismissObjectDrop = true;
        } else if (cursor.isOver(buttonPosition, buttonSize) && cursor.isMousePressed() && eventState->lastUsedFigureButton != button) {
            cancelDragging(cursor);
        }
    }
}

void ButtonFigureEventHandler::doMouseOver(Cursor &cursor, std::shared_ptr<FigureButton> button) {
    if (!eventRegistry->isOverRegistered(button)) {
        eventRegistry->registerOver(button);
        button->mouseEnter(animationPerformer);
    } else {
        button->mouseOver(animationPerformer);
    }
}

void ButtonFigureEventHandler::doMouseOut(Cursor &cursor, std::shared_ptr<FigureButton> button) {
    eventRegistry->unregisterOver(button);
    button->mouseLeave(animationPerformer);
}

void ButtonFigureEventHandler::doMouseClick(Cursor &cursor, std::shared_ptr<FigureButton> button) {
    createFigureSnappedToCursor(cursor, button);
    eventState->lastUsedFigureButton = button;
    eventState->isDraggingNewObject = true;
    eventState->clickedOnTileButton = true;
}

void ButtonFigureEventHandler::createFigureSnappedToCursor(Cursor &cursor, std::shared_ptr<FigureButton> button) {
    auto mainGrid = scene->getGrid();
    auto dynamicFigure = button->cloneToDynamicFigure(tileFactory, mainGrid);

    auto initialGridPosition = mainGrid->positionToPointOnGrid(cursor.getPosition());
    dynamicFigure->snapToGrid(initialGridPosition);

    dynamicFigure->mouseEnter(animationPerformer);
    eventRegistry->registerOver(dynamicFigure);

    dynamicFigure->startDrag(cursor.getPosition(), animationPerformer);
    cursor.draggedItem = dynamicFigure;
    eventRegistry->registerDrag(dynamicFigure);

}

void ButtonFigureEventHandler::cancelDragging(Cursor &cursor) {
    auto draggingFigure = scene->getDraggingFigure();
    eventRegistry->unregisterDrag(draggingFigure);
    ObjectRegistry::removeFigure(draggingFigure);

    std::shared_ptr<Grid> grid = scene->getGrid();
    grid->turnHighlightOff();
    eventState->isDraggingNewObject = false;
    cursor.draggedItem.reset();
}