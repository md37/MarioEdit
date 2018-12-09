#include "EventHandler.hpp"

#include "classes/Infrastructure/Log.hpp"

class ChangeVariantVisitator {

public:

    explicit ChangeVariantVisitator(sf::Uint8 variant) {
        this->variant = variant;
    }

    void operator()(std::shared_ptr<DynamicTile>& tile) {}

    void operator()(std::shared_ptr<Figure>& figure) {
        figure->changeVariant(variant);
    }

private:

    sf::Uint8 variant;
};

EditorEventHandler::EditorEventHandler(
    std::unique_ptr<AnimationPerformer> &animationPerformer,
    std::unique_ptr<Scene> &scene,
    std::unique_ptr<TileFactory> &tileFactory
) {
    currentState = std::make_unique<EventState>();
    eventRegistry = std::make_unique<EventRegistry>();

    buttonTileEventHandler = std::make_unique<ButtonTileEventHandler>(
        currentState, animationPerformer, scene, tileFactory, eventRegistry
    );

    dynamicTileEventHandler = std::make_unique<DynamicTileEventHandler>(
        currentState, animationPerformer, scene, tileFactory, eventRegistry
    );

    figureEventHandler = std::make_unique<FigureEventHandler>(
        animationPerformer, eventRegistry
    );
}

void EditorEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    currentState->dismissTileDrop = false;

    auto pressedNumeric = keyboard.getPressedNumeric();
    auto draggingItem = cursor.draggedItem;
    if (pressedNumeric != std::nullopt && draggingItem) {
        std::visit(ChangeVariantVisitator(pressedNumeric.value()), draggingItem.value());
    }

    buttonTileEventHandler->handleEvents(keyboard, cursor);
    dynamicTileEventHandler->handleEvents(keyboard, cursor);
    figureEventHandler->handleEvents(keyboard, cursor);
}
