#include "DynamicTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

DynamicTileEventHandler::DynamicTileEventHandler(
    std::shared_ptr<EventState> eventState,
    std::shared_ptr<AnimationPerformer> animationPerformer,
    std::shared_ptr<Scene> scene,
    std::shared_ptr<TileFactory> tileFactory
) : AbstractTileEventHandler(eventState, animationPerformer, scene, tileFactory) {

}

void DynamicTileEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    if (eventState->isDraggingNewTile) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        bool isEscape = keyboard.isPressed(sf::Keyboard::Key::Escape);

        if (cursor.isClick() && cursor.isLongClick() && !eventState->clickedOnTileButton) {
            performLongClickDrop(cursor);
        } else if (cursor.isMouseReleased() && isLeftClick) {
            performQuickClickDrop(cursor);
        } else if (!isLeftClick || isEscape) {
            cancelDragging(cursor);
        }
    } else {
        auto tiles = ObjectRegistry::getDynamicTiles();

        for (auto &tile : tiles) {
            performHover(cursor, tile);
        }

        for (auto &tile : tiles) {
            performDragDrop(cursor, tile);
        }
    }
}

void DynamicTileEventHandler::performDragDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    if (cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        if (cursor.isClick() && !cursor.isDragRegistered(tile) && isLeftClick) {
            tile->startDrag(animationPerformer);
            cursor.registerDrag(tile);
        } else if (!cursor.isClick() && cursor.isDragRegistered(tile)) {
            performDrop(cursor, tile);
        }
    } else if (cursor.isOverRegistered(tile) && cursor.isDragRegistered(tile)) {
        performDrop(cursor, tile);
    }
}

void DynamicTileEventHandler::performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto dropHighlightPlace = scene->getGrid()->getHighlightPlace();
    auto tileOnThisPlace = ObjectRegistry::getTileOnGrid(dropHighlightPlace);

    if (tileOnThisPlace != nullptr && tileOnThisPlace != tile) {
        ObjectRegistry::removeTile(tileOnThisPlace);
    }

    cursor.unregisterDrag(tile);
    tile->drop(animationPerformer);
}

void DynamicTileEventHandler::performHover(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto highlightedTiles = ObjectRegistry::getHighlightedTiles();

    if (highlightedTiles.empty()) {
        if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
            cursor.registerOver(tile);
            tile->mouseEnter(animationPerformer);
        } else if (cursor.isOver(tile)) {
            tile->mouseOver(animationPerformer);
        }
    } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
        cursor.unregisterOver(tile);
        tile->mouseLeave(animationPerformer);
    }
}

void DynamicTileEventHandler::performLongClickDrop(Cursor &cursor) {
    auto grid = scene->getGrid();
    auto currentSlotGridPosition = grid->positionToGridPlace(cursor.getCurrentPosition());
    auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);

    auto draggingTile = scene->getDraggingTile();
    bool insertTile = tileOnCurrentSlot == nullptr || tileOnCurrentSlot == draggingTile;
    if (!insertTile) {
        bool tileIsSameType = tileOnCurrentSlot->isTypeOf(eventState->lastUsedTileButton);
        if (!tileIsSameType) {
            insertTile = true;
            ObjectRegistry::removeTile(tileOnCurrentSlot);
        }
    }

    if (insertTile) {
        draggingTile->drop(animationPerformer);
        draggingTile->snapToGrid();
        cursor.unregisterDrag(draggingTile);
        createDynamicTileSnappedToCursor(cursor, eventState->lastUsedTileButton);
    }
}

void DynamicTileEventHandler::performQuickClickDrop(Cursor &cursor) {
    eventState->clickedOnTileButton = false;
    if (eventState->dismissTileDrop) {
        return;
    }

    auto grid = scene->getGrid();
    auto currentSlotGridPosition = grid->positionToGridPlace(cursor.getCurrentPosition());
    auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);

    auto draggingTile = scene->getDraggingTile();
    if (tileOnCurrentSlot != nullptr && tileOnCurrentSlot != draggingTile) {
        ObjectRegistry::removeTile(tileOnCurrentSlot);
    }
    draggingTile->drop(animationPerformer);
    cursor.unregisterDrag(draggingTile);
    eventState->isDraggingNewTile = false;
}
