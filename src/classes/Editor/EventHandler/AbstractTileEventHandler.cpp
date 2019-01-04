#include "AbstractTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

AbstractTileEventHandler::AbstractTileEventHandler(
    std::unique_ptr<EventState> &eventState,
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory,
    std::unique_ptr<EventRegistry> &eventRegistry
): tileFactory(tileFactory), scene(scene), animationPerformer(animationPerformer), eventState(eventState), eventRegistry(eventRegistry) {

}

void AbstractTileEventHandler::createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<TileButton> button) {
    auto dynamicTile = button->cloneToDynamicTile(tileFactory, scene->getGrid());

    auto tilePosition = cursor.getPosition();
    tilePosition.x -= dynamicTile->getSize().x/2;
    tilePosition.y -= dynamicTile->getSize().y/2;

    dynamicTile->setPosition(tilePosition);
    dynamicTile->startDrag(cursor.getPosition(), animationPerformer);
    cursor.draggedItem = dynamicTile;
    eventRegistry->registerDrag(dynamicTile);
}

void AbstractTileEventHandler::cancelDragging(Cursor &cursor) {
    auto draggingTile = scene->getDraggingTile();
    eventRegistry->unregisterDrag(draggingTile);
    ObjectRegistry::removeTile(draggingTile);

    std::shared_ptr<Grid> grid = scene->getGrid();
    grid->turnHighlightOff();
    eventState->isDraggingNewTile = false;
    cursor.draggedItem.reset();
}
