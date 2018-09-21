#include "Editor.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

Editor::Editor(std::shared_ptr<TileFactory> tileFactory, std::shared_ptr<Scale> scale) {
    navigation = std::make_shared<Navigation>(tileFactory);
    scene = std::make_shared<Scene>(tileFactory, scale);
}

void Editor::start() {
    isStartedFlag = true;
    scene->startTasks();
}

void Editor::rescale(sf::Vector2u windowSize) {
    scene->rescale(windowSize);
    navigation->rescale(windowSize);
}

void Editor::draw(std::shared_ptr<sf::RenderWindow> window) {
    scene->draw(window);
    navigation->draw(window);
}

bool Editor::isStarted() {
    return isStartedFlag;
}

void Editor::handleEvents(Keyboard& keyboard, Cursor& cursor) {
    handleButtonTilesEvents(keyboard, cursor);
    handleSceneTilesEvents(keyboard, cursor);
}

void Editor::handleButtonTilesEvents(Keyboard& keyboard, Cursor& cursor) {
    auto tiles = ObjectRegistry::getButtonTiles();

    for (auto &tile : tiles) {
        if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
            cursor.registerOver(tile);
            tile->mouseEnter();
        } else if (cursor.isOver(tile)) {
            tile->mouseOver();
        } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
            cursor.unregisterOver(tile);
            tile->mouseLeave();
        }
    }
}

void Editor::handleSceneTilesEvents(Keyboard& keyboard, Cursor& cursor) {
    auto tiles = ObjectRegistry::getDynamicTiles();

    for (auto &tile : tiles) {
        if (cursor.isDragRegistered(tile)) {
            if (cursor.isClick()) {
                tile->drag();
            } else {
                cursor.unregisterDrag(tile);
                tile->drop();
            }
            return;
        }
    }

    for (auto &tile : tiles) {
        if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
            cursor.registerOver(tile);
            tile->mouseEnter();
        } else if (cursor.isOver(tile)) {
            tile->mouseOver();
        } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
            cursor.unregisterOver(tile);
            tile->mouseLeave();
        }
    }

    for (auto &tile : tiles) {
        if (cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
            if (cursor.isClick() && !cursor.isDragRegistered(tile)) {
                cursor.registerDrag(tile);
                tile->startDrag();
            } else if (!cursor.isClick() && cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->drop();
            }
        } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
            if (cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->drop();
            }
        } else if (cursor.isDragRegistered(tile)) {
            cursor.unregisterDrag(tile);
            tile->drop();
        }
    }
}
