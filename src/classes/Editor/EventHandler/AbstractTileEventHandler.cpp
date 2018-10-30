#include "AbstractTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

AbstractTileEventHandler::AbstractTileEventHandler(
    std::shared_ptr<EventState> eventState,
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory,
    std::shared_ptr<TileEventRegistry> tileEventRegistry
): tileFactory(tileFactory), scene(scene), animationPerformer(animationPerformer) {
    this->eventState = eventState;
    this->tileEventRegistry = tileEventRegistry;
}

void AbstractTileEventHandler::createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    auto dynamicTile = button->cloneToDynamicTile(tileFactory);
    dynamicTile->setGrid(scene->getGrid());

    auto tilePosition = cursor.getCurrentPosition();
    tilePosition.x -= dynamicTile->getSize().x/2;
    tilePosition.y -= dynamicTile->getSize().y/2;

    dynamicTile->setPosition(tilePosition);
    dynamicTile->startDrag(animationPerformer);
    tileEventRegistry->registerDrag(dynamicTile);
}

void AbstractTileEventHandler::cancelDragging(Cursor &cursor) {
    auto draggingTile = scene->getDraggingTile();
    tileEventRegistry->unregisterDrag(draggingTile);
    ObjectRegistry::removeTile(draggingTile);

    auto grid = scene->getGrid();
    grid->turnHighlightOff();
    eventState->isDraggingNewTile = false;
}
