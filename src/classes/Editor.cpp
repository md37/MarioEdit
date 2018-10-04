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
    dismissTileDrop = false;
    handleButtonTilesEvents(keyboard, cursor);
    handleSceneTilesEvents(keyboard, cursor);
}

void Editor::handleButtonTilesEvents(Keyboard& keyboard, Cursor& cursor) {
    auto buttons = ObjectRegistry::getButtonTiles();
    if (!isDraggingNewTile) {
        for (auto &button: buttons) {
            if (cursor.isOver(button)) {
                doButtonMouseOver(cursor, button);

                if (cursor.isMousePressed()) {
                    doButtonMouseClick(cursor, button);
                    lastUsedTileButton = button;
                    isDraggingNewTile = true;
                    clickedOnTileButton = true;
                }
                break;
            } else if (cursor.isOverRegistered(button)) {
                doButtonMouseOut(cursor, button);
                break;
            }
        }
        return;
    }

    for (auto &button: buttons) {
        if (cursor.isOver(button) && cursor.isMouseReleased()) {
            dismissTileDrop = true;
        } else if (cursor.isOver(button) && cursor.isMousePressed() && lastUsedTileButton != button) {
            cancelDragging(cursor);
        }
    }
}

void Editor::doButtonMouseOver(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    if (!cursor.isOverRegistered(button)) {
        cursor.registerOver(button);
        button->mouseEnter(animationPerformer);
    } else {
        button->mouseOver(animationPerformer);
    }
}

void Editor::doButtonMouseOut(Cursor &cursor, std::shared_ptr<ButtonTile> button) {
    cursor.unregisterOver(button);
    button->mouseLeave(animationPerformer);
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
    dynamicTile->startDrag(animationPerformer);
    cursor.registerDrag(dynamicTile);
}

void Editor::handleSceneTilesEvents(Keyboard& keyboard, Cursor& cursor) {
    if (isDraggingNewTile) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        bool isEscape = keyboard.isPressed(sf::Keyboard::Key::Escape);
        
        if (cursor.isClick() && cursor.isLongClick() && !clickedOnTileButton) {
            performLongClickDrop(cursor);
        } else if (cursor.isMouseReleased() && isLeftClick) {
            performQuickClickDrop(cursor);
        } else if (!isLeftClick || isEscape) {
            cancelDragging(cursor);
        }
    } else {
        auto tiles = ObjectRegistry::getDynamicTiles();

        for (auto &tile : tiles) {
            performHover(cursor, tile);
        }

        for (auto &tile : tiles) {
            performDragDrop(cursor, tile);
        }
    }
}

void Editor::performDragDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    if (cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
        bool isLeftClick = cursor.getClickType() == sf::Mouse::Button::Left;
        if (cursor.isClick() && !cursor.isDragRegistered(tile) && isLeftClick) {
            tile->startDrag(animationPerformer);
            cursor.registerDrag(tile);
        } else if (!cursor.isClick() && cursor.isDragRegistered(tile)) {
            performDrop(cursor, tile);
        }
    } else if (cursor.isOverRegistered(tile) && cursor.isDragRegistered(tile)) {
        performDrop(cursor, tile);
    }
}

void Editor::performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto dropHighlightPlace = scene->getGrid()->getHighlightPlace();
    auto tileOnThisPlace = ObjectRegistry::getTileOnGrid(dropHighlightPlace);

    if (tileOnThisPlace != nullptr && tileOnThisPlace != tile) {
        ObjectRegistry::removeTile(tileOnThisPlace);
    }

    cursor.unregisterDrag(tile);
    tile->drop(animationPerformer);
}

void Editor::performHover(Cursor &cursor, std::shared_ptr<DynamicTile> &tile) {
    auto highlightedTiles = ObjectRegistry::getHighlightedTiles();

    if (highlightedTiles.empty()) {
        if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
            cursor.registerOver(tile);
            tile->mouseEnter(animationPerformer);
        } else if (cursor.isOver(tile)) {
            tile->mouseOver(animationPerformer);
        }
    } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
        cursor.unregisterOver(tile);
        tile->mouseLeave(animationPerformer);
    }
}

void Editor::performLongClickDrop(Cursor &cursor) {
    auto grid = scene->getGrid();
    auto currentSlotGridPosition = grid->positionToGridPlace(cursor.getCurrentPosition());
    auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);

    auto draggingTile = scene->getDraggingTile();
    bool insertTile = tileOnCurrentSlot == nullptr || tileOnCurrentSlot == draggingTile;
    if (!insertTile) {
        bool tileIsSameType = tileOnCurrentSlot->isTypeOf(lastUsedTileButton);
        if (!tileIsSameType) {
            insertTile = true;
            ObjectRegistry::removeTile(tileOnCurrentSlot);
        }
    }

    if (insertTile) {
        draggingTile->drop(animationPerformer);
        draggingTile->snapToGrid();
        cursor.unregisterDrag(draggingTile);
        createDynamicTileSnappedToCursor(cursor, lastUsedTileButton);
    }
}

void Editor::performQuickClickDrop(Cursor &cursor) {
    clickedOnTileButton = false;
    if (dismissTileDrop) {
        return;
    }

    auto grid = scene->getGrid();
    auto currentSlotGridPosition = grid->positionToGridPlace(cursor.getCurrentPosition());
    auto tileOnCurrentSlot = ObjectRegistry::getTileOnGrid(currentSlotGridPosition);

    auto draggingTile = scene->getDraggingTile();
    if (tileOnCurrentSlot != nullptr && tileOnCurrentSlot != draggingTile) {
        ObjectRegistry::removeTile(tileOnCurrentSlot);
    }
    draggingTile->drop(animationPerformer);
    cursor.unregisterDrag(draggingTile);
    isDraggingNewTile = false;
}

void Editor::cancelDragging(Cursor &cursor) {
    auto draggingTile = scene->getDraggingTile();
    cursor.unregisterDrag(draggingTile);
    ObjectRegistry::removeTile(draggingTile);

    auto grid = scene->getGrid();
    grid->turnHighlightOff();
    isDraggingNewTile = false;
}

void Editor::runAnimations() {
    animationPerformer.process();
}
