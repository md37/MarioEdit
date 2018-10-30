#include "EventHandler.hpp"

EditorEventHandler::EditorEventHandler(
    std::shared_ptr<AnimationPerformer> animationPerformer,
    std::shared_ptr<Scene> scene,
    std::shared_ptr<TileFactory> tileFactory
) {
    currentState = std::make_shared<EventState>();
    tileEventRegistry = std::make_shared<TileEventRegistry>();
    figureEventRegistry = std::make_shared<FigureEventRegistry>();

    buttonTileEventHandler = std::make_shared<ButtonTileEventHandler>(
        currentState, animationPerformer, scene, tileFactory, tileEventRegistry
    );

    dynamicTileEventHandler = std::make_shared<DynamicTileEventHandler>(
        currentState, animationPerformer, scene, tileFactory, tileEventRegistry
    );

    figureEventHandler = std::make_shared<FigureEventHandler>(
        animationPerformer, figureEventRegistry
    );
}

void EditorEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    currentState->dismissTileDrop = false;

    buttonTileEventHandler->handleEvents(keyboard, cursor);
    dynamicTileEventHandler->handleEvents(keyboard, cursor);
    figureEventHandler->handleEvents(keyboard, cursor);
}
