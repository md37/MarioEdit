#include "ButtonTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

ButtonTileEventHandler::ButtonTileEventHandler(
    std::shared_ptr<EventState> eventState,
    std::shared_ptr<AnimationPerformer> animationPerformer,
    std::shared_ptr<Scene> scene,
    std::shared_ptr<TileFactory> tileFactory,
    std::shared_ptr<TileEventRegistry> tileEventRegistry
) : AbstractTileEventHandler(eventState, animationPerformer, scene, tileFactory, tileEventRegistry) {

}

void ButtonTileEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    auto buttons = ObjectRegistry::getButtonTiles();
    if (!eventState->isDraggingNewTile) {
        for (auto &button: buttons) {
            if (cursor.isOver(button)) {
                doMouseOver(cursor, button);

                if (cursor.isMousePressed()) {
                    doMouseClick(cursor, button);
                }
                break;
            } else if (tileEventRegistry->isOverRegistered(button)) {
                doMouseOut(cursor, button);
                break;
            }
        }
        return;
    }

    for (auto &button: buttons) {
        if (cursor.isOver(button) && cursor.isMouseReleased()) {
            eventState->dismissTileDrop = true;
        } else if (cursor.isOver(button) && cursor.isMousePressed() && eventState->lastUsedTileButton != button) {
            cancelDragging(cursor);
        }
    }
}

void ButtonTileEventHandler::doMouseOver(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    if (!tileEventRegistry->isOverRegistered(button)) {
        tileEventRegistry->registerOver(button);
        button->mouseEnter(animationPerformer);
    } else {
        button->mouseOver(animationPerformer);
    }
}

void ButtonTileEventHandler::doMouseOut(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    tileEventRegistry->unregisterOver(button);
    button->mouseLeave(animationPerformer);
}

void ButtonTileEventHandler::doMouseClick(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    createDynamicTileSnappedToCursor(cursor, button);
    eventState->lastUsedTileButton = button;
    eventState->isDraggingNewTile = true;
    eventState->clickedOnTileButton = true;
}