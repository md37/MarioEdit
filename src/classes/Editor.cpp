#include "Editor.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

Editor::Editor(std::shared_ptr<TileFactory> tileFactory) {
    this->tileFactory = tileFactory;
    navigation = std::make_shared<Navigation>(tileFactory);
    scene = std::make_shared<Scene>(tileFactory);
    animationPerformer = std::make_shared<AnimationPerformer>();
    eventHandler = std::make_shared<EditorEventHandler>(animationPerformer, scene, tileFactory);
}

void Editor::start() {
    animationPerformer->start();
    isStartedFlag = true;
}

void Editor::rescale(std::shared_ptr<Scale> scale) {
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
