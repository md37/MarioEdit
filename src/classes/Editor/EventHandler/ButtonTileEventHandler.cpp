#include "ButtonTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

ButtonTileEventHandler::ButtonTileEventHandler(
    std::unique_ptr<EventState> &eventState,
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory,
    std::unique_ptr<EventRegistry> &tileEventRegistry
) : AbstractTileEventHandler(eventState, animationPerformer, scene, tileFactory, tileEventRegistry) {

}

void ButtonTileEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    auto buttons = ObjectRegistry::getButtonTiles();
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
        } else if (cursor.isOver(buttonPosition, buttonSize) && cursor.isMousePressed() && eventState->lastUsedTileButton != button) {
            cancelDragging(cursor);
        }
    }
}

void ButtonTileEventHandler::doMouseOver(Cursor &cursor, std::shared_ptr<TileButton> button) {
    if (!eventRegistry->isOverRegistered(button)) {
        eventRegistry->registerOver(button);
        button->mouseEnter(animationPerformer);
    } else {
        button->mouseOver(animationPerformer);
    }
}

void ButtonTileEventHandler::doMouseOut(Cursor &cursor, std::shared_ptr<TileButton> button) {
    eventRegistry->unregisterOver(button);
    button->mouseLeave(animationPerformer);
}

void ButtonTileEventHandler::doMouseClick(Cursor &cursor, std::shared_ptr<TileButton> button) {
    createDynamicTileSnappedToCursor(cursor, button);
    eventState->lastUsedTileButton = button;
    eventState->isDraggingNewObject = true;
    eventState->clickedOnTileButton = true;
}