#include "Editor.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

Editor::Editor(std::shared_ptr<TileFactory> tileFactory) {
    this->tileFactory = tileFactory;
    navigation = std::make_shared<Navigation>(tileFactory);
    scene = std::make_shared<Scene>(tileFactory);
}

void Editor::start() {
    isStartedFlag = true;
    scene->startTasks();
}

void Editor::rescale(std::shared_ptr<Scale> scale) {
    scene->rescale(scale);
    navigation->rescale(scale);
}

void Editor::draw(std::shared_ptr<sf::RenderWindow> window) {
    scene->draw(window);
    navigation->draw(window);

    if (isDraggingTile) {
        auto draggingTile = scene->getDraggingTile();
        draggingTile->draw(window);
    }
}

bool Editor::isStarted() {
    return isStartedFlag;
}

void Editor::handleEvents(Keyboard& keyboard, Cursor& cursor) {
    dismissTileDrop = false;
    handleButtonTilesEvents(keyboard, cursor);
    handleSceneTilesEvents(keyboard, cursor);
}

void Editor::handleButtonTilesEvents(Keyboard& keyboard, Cursor& cursor) {
    auto buttons = ObjectRegistry::getButtonTiles();
    if (!isDraggingTile) {
        for (auto &button: buttons) {
            if (cursor.isOver(button)) {
                doButtonMouseOver(cursor, button);

                if (cursor.isMousePressed()) {
                    doButtonMouseClick(cursor, button);
                    lastUsedTileButton = button;
                    isDraggingTile = true;
                    clickedOnTileButton = true;
                }
                break;
            } else if (cursor.isOverRegistered(button)) {
                doButtonMouseOut(cursor, button);
                break;
            }
        }
    } else if (isDraggingTile) {
        for (auto &button: buttons) {
            if (cursor.isOver(button) && cursor.isMouseReleased()) {
                dismissTileDrop = true;
            }
        }
    }
}

void Editor::doButtonMouseOver(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    if (!cursor.isOverRegistered(button)) {
        cursor.registerOver(button);
        button->mouseEnter();
    } else {
        button->mouseOver();
    }
}

void Editor::doButtonMouseOut(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    cursor.unregisterOver(button);
    button->mouseLeave();
}

void Editor::doButtonMouseClick(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    createDynamicTileSnappedToCursor(cursor, button);
}

void Editor::createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    auto dynamicTile = button->cloneToDynamicTile(tileFactory);
    dynamicTile->setGrid(scene->getGrid());

    auto tilePosition = cursor.getCurrentPosition();
    tilePosition.x -= dynamicTile->getSize().x/2;
    tilePosition.y -= dynamicTile->getSize().y/2;

    dynamicTile->setPosition(tilePosition);
    dynamicTile->startDrag();
    cursor.registerDrag(dynamicTile);
}

void Editor::handleSceneTilesEvents(Keyboard& keyboard, Cursor& cursor) {
    if (isDraggingTile) {
        auto clickDuration = cursor.getClickDuration();
        auto grid = scene->getGrid();

        auto currentSlotGridPosition = grid->positionToGridPlace(cursor.getCurrentPosition());
        auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);
        auto draggingTile = scene->getDraggingTile();

        if (cursor.isClick() && cursor.isLongClick() && isDraggingTile && !clickedOnTileButton) {
            bool insertTile = false;
            if (tileOnCurrentSlot != nullptr && tileOnCurrentSlot != draggingTile) {
                bool tileIsSameType = tileOnCurrentSlot->isTypeOf(lastUsedTileButton);
                if (!tileIsSameType) {
                    insertTile = true;
                    ObjectRegistry::removeTile(tileOnCurrentSlot);
                }
            } else {
                insertTile = true;
            }

            if (insertTile) {
                draggingTile->drop();
                cursor.unregisterDrag(draggingTile);
                createDynamicTileSnappedToCursor(cursor, lastUsedTileButton);
            }
        } else if (cursor.isMouseReleased()) {
            clickedOnTileButton = false;
            if (isDraggingTile && !dismissTileDrop) {
                if (tileOnCurrentSlot != nullptr && tileOnCurrentSlot != draggingTile) {
                    ObjectRegistry::removeTile(tileOnCurrentSlot);
                }
                draggingTile->drop();
                cursor.unregisterDrag(draggingTile);
                isDraggingTile = false;
            }
        }
    } else {
        auto tiles = ObjectRegistry::getDynamicTiles();

        for (auto &tile : tiles) {
            auto highlightedTiles = ObjectRegistry::getHighlightedTiles();
            if (highlightedTiles.empty()) {
                if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
                    cursor.registerOver(tile);
                    tile->mouseEnter();
                } else if (cursor.isOver(tile)) {
                    tile->mouseOver();
                }
            } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
                cursor.unregisterOver(tile);
                tile->mouseLeave();
            }
        }
    }
}

void Editor::performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto dropHighlightPlace = scene->getGrid()->getHighlightPlace();
    auto tileOnThisPlace = ObjectRegistry::getTileOnGrid(dropHighlightPlace);

    cursor.unregisterDrag(tile);
    tile->drop();

    if (tileOnThisPlace != nullptr && tileOnThisPlace != tile) {
        cursor.registerOver(tileOnThisPlace);
        tileOnThisPlace->mouseEnter();

        cursor.registerDrag(tileOnThisPlace);
        tileOnThisPlace->startDrag();
    }
}