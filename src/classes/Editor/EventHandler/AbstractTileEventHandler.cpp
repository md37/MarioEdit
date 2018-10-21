#include "AbstractTileEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

AbstractTileEventHandler::AbstractTileEventHandler(
    std::shared_ptr<EventState> eventState,
    std::shared_ptr<AnimationPerformer> animationPerformer,
    std::shared_ptr<Scene> scene,
    std::shared_ptr<TileFactory> tileFactory
) {
    this->eventState = eventState;
    this->animationPerformer = animationPerformer;
    this->scene = scene;
    this->tileFactory = tileFactory;
}

void AbstractTileEventHandler::createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    auto dynamicTile = button->cloneToDynamicTile(tileFactory);
    dynamicTile->setGrid(scene->getGrid());

    auto tilePosition = cursor.getCurrentPosition();
    tilePosition.x -= dynamicTile->getSize().x/2;
    tilePosition.y -= dynamicTile->getSize().y/2;

    dynamicTile->setPosition(tilePosition);
    dynamicTile->startDrag(animationPerformer);
    cursor.registerDrag(dynamicTile);
}

void AbstractTileEventHandler::cancelDragging(Cursor &cursor) {
    auto draggingTile = scene->getDraggingTile();
    cursor.unregisterDrag(draggingTile);
    ObjectRegistry::removeTile(draggingTile);

    auto grid = scene->getGrid();
    grid->turnHighlightOff();
    eventState->isDraggingNewTile = false;
}
