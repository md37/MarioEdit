#include "EventHandler.hpp"

EditorEventHandler::EditorEventHandler(
    std::shared_ptr<AnimationPerformer> animationPerformer,
    std::shared_ptr<Scene> scene,
    std::shared_ptr<TileFactory> tileFactory
) {
    currentState = std::make_shared<EventState>();
    buttonTileEventHandler = std::make_shared<ButtonTileEventHandler>(currentState, animationPerformer, scene, tileFactory);
    dynamicTileEventHandler = std::make_shared<DynamicTileEventHandler>(currentState, animationPerformer, scene, tileFactory);
}

void EditorEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    currentState->dismissTileDrop = false;

    buttonTileEventHandler->handleEvents(keyboard, cursor);
    dynamicTileEventHandler->handleEvents(keyboard, cursor);
}
