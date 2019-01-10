#include "AbstractFigureEventHandler.hpp"

AbstractFigureEventHandler::AbstractFigureEventHandler(
    std::unique_ptr<EventState> &eventState,
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory,
    std::unique_ptr<EventRegistry> &eventRegistry
):
    eventState(eventState), animationPerformer(animationPerformer), scene(scene), tileFactory(tileFactory), eventRegistry(eventRegistry) {
}
