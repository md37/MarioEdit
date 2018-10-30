#include "Editor.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

Editor::Editor(std::unique_ptr<TileFactory> &tileFactory): tileFactory(tileFactory) {
    navigation = std::make_unique<Navigation>(tileFactory);
    scene = std::make_unique<Scene>(tileFactory);
    animationPerformer = std::make_unique<AnimationPerformer>();
    eventHandler = std::make_unique<EditorEventHandler>(animationPerformer, scene, tileFactory);
}

void Editor::start() {
    animationPerformer->start();
    isStartedFlag = true;
}

void Editor::rescale(std::unique_ptr<Scale>& scale) {
    scene->rescale(scale);
    navigation->rescale(scale);
}

void Editor::draw(std::shared_ptr<sf::RenderWindow> window) {
    scene->draw(window);
    navigation->draw(window);

    auto draggingTile = scene->getDraggingTile();
    bool isDraggingTile = draggingTile.use_count() > 0;
    if (isDraggingTile) {
        draggingTile->draw(window);
    }
}

bool Editor::isStarted() {
    return isStartedFlag;
}

void Editor::handleEvents(Keyboard& keyboard, Cursor& cursor) {
    eventHandler->handleEvents(keyboard, cursor);
}

void Editor::runAnimations() {
    animationPerformer->process();
}
