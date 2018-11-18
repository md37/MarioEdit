#include "DynamicTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

class DragVisitator {

public:

    explicit DragVisitator(Cursor &cursor) : cursor(cursor) {

    }

    void operator()(std::shared_ptr<DynamicTile>& tile) {
        tile->drag(cursor.getPosition());
    }

    void operator()(std::shared_ptr<Figure>& figure) {}

private:

    Cursor &cursor;

};

DynamicTileEventHandler::DynamicTileEventHandler(
    std::unique_ptr<EventState> &eventState,
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory,
    std::unique_ptr<EventRegistry> &eventRegistry
) : AbstractTileEventHandler(eventState, animationPerformer, scene, tileFactory, eventRegistry) {

}

void DynamicTileEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    if (cursor.isMouseMoved()) {
        auto registeredDragOnTiles = eventRegistry->getRegisteredDrags();
        for (auto &dragOnItem : registeredDragOnTiles) {
            DragVisitator visitator(cursor);
            std::visit(visitator, dragOnItem);
        }
    }

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

void DynamicTileEventHandler::performHover(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto highlightedTiles = ObjectRegistry::getHighlightedTiles();
    auto tilePosition = tile->getPosition();
    auto tileSize = tile->getSize();

    if (highlightedTiles.empty()) {
        bool isDraggingItem = cursor.draggedItem.has_value();
        if (cursor.isOver(tilePosition, tileSize) && !eventRegistry->isOverRegistered(tile) && !isDraggingItem) {
            eventRegistry->registerOver(tile);
            tile->mouseEnter(animationPerformer);
        } else if (cursor.isOver(tilePosition, tileSize)) {
            tile->mouseOver(animationPerformer);
        }
    } else if (!cursor.isOver(tilePosition, tileSize) && eventRegistry->isOverRegistered(tile)) {
        eventRegistry->unregisterOver(tile);
        tile->mouseLeave(animationPerformer);
    }
}

void DynamicTileEventHandler::performDragDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto tilePosition = tile->getPosition();
    auto tileSize = tile->getSize();
    if (cursor.isOver(tilePosition, tileSize) && eventRegistry->isOverRegistered(tile)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        bool isDraggingItem = cursor.draggedItem.has_value();
        if (cursor.isClick() && !eventRegistry->isDragRegistered(tile) && isLeftClick && !isDraggingItem) {
            tile->startDrag(cursor.getPosition(), animationPerformer);
            eventRegistry->registerDrag(tile);
            cursor.draggedItem = tile;
        } else if (!cursor.isClick() && eventRegistry->isDragRegistered(tile)) {
            performDrop(cursor, tile);
        }
    } else if (eventRegistry->isDragRegistered(tile)) {
        performDrop(cursor, tile);
    }
}

void DynamicTileEventHandler::performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto dropHighlightPlace = scene->getGrid()->getHighlightPointOnGrid();
    auto tileOnThisPlace = ObjectRegistry::getTileOnGrid(dropHighlightPlace);

    if (tileOnThisPlace != nullptr && tileOnThisPlace != tile) {
        ObjectRegistry::removeTile(tileOnThisPlace);
    }

    eventRegistry->unregisterDrag(tile);
    tile->drop(animationPerformer);
    cursor.draggedItem.reset();
}

void DynamicTileEventHandler::performLongClickDrop(Cursor &cursor) {
    auto grid = scene->getGrid();
    auto currentSlotGridPosition = grid->positionToPointOnGrid(cursor.getPosition());
    auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);

    auto draggingTile = scene->getDraggingTile();
    bool insertTile = tileOnCurrentSlot == nullptr || tileOnCurrentSlot == draggingTile;
    cursor.draggedItem.reset();

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
        eventRegistry->unregisterDrag(draggingTile);
        createDynamicTileSnappedToCursor(cursor, eventState->lastUsedTileButton);
    }
}

void DynamicTileEventHandler::performQuickClickDrop(Cursor &cursor) {
    eventState->clickedOnTileButton = false;
    if (eventState->dismissTileDrop) {
        return;
    }

    auto grid = scene->getGrid();
    auto currentSlotGridPosition = grid->positionToPointOnGrid(cursor.getPosition());
    auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);

    auto draggingTile = scene->getDraggingTile();
    if (tileOnCurrentSlot != nullptr && tileOnCurrentSlot != draggingTile) {
        ObjectRegistry::removeTile(tileOnCurrentSlot);
    }
    draggingTile->drop(animationPerformer);
    eventRegistry->unregisterDrag(draggingTile);
    eventState->isDraggingNewTile = false;
    cursor.draggedItem.reset();
}
