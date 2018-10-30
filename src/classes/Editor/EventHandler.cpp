#include "EventHandler.hpp"

EditorEventHandler::EditorEventHandler(
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory
) {
    currentState = std::make_unique<EventState>();
    tileEventRegistry = std::make_unique<TileEventRegistry>();
    figureEventRegistry = std::make_unique<FigureEventRegistry>();

    buttonTileEventHandler = std::make_unique<ButtonTileEventHandler>(
        currentState, animationPerformer, scene, tileFactory, tileEventRegistry
    );

    dynamicTileEventHandler = std::make_unique<DynamicTileEventHandler>(
        currentState, animationPerformer, scene, tileFactory, tileEventRegistry
    );

    figureEventHandler = std::make_unique<FigureEventHandler>(
        animationPerformer, figureEventRegistry
    );
}

void EditorEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    currentState->dismissTileDrop = false;

    buttonTileEventHandler->handleEvents(keyboard, cursor);
    dynamicTileEventHandler->handleEvents(keyboard, cursor);
    figureEventHandler->handleEvents(keyboard, cursor);
}
