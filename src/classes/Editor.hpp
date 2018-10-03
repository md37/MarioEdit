#pragma once

#include "classes/System/Interface/RunnableInterface.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"
#include "classes/Editor/Navigation.hpp"
#include "classes/Editor/Scene.hpp"

class Editor : public RunnableInterface, public RescalableInterface, public DrawableInterface, public EventReceiverableInterface {

public:

    Editor(std::shared_ptr<TileFactory> tileFactory);

    void start() override;
    bool isStarted() override;

    void rescale(std::shared_ptr<Scale> scale) override;
    void draw(std::shared_ptr<sf::RenderWindow> window) override;

    void handleEvents(Keyboard& keyboard, Cursor& cursor) override;

private:

    bool isStartedFlag = false;
    std::shared_ptr<TileFactory> tileFactory;
    std::shared_ptr<Navigation> navigation;
    std::shared_ptr<Scene> scene;
    AnimationPerformer animationPerformer;

    bool isDraggingNewTile = false;
    bool dismissTileDrop = false;
    bool clickedOnTileButton = false;
    std::shared_ptr<ButtonTile> lastUsedTileButton;

    void handleButtonTilesEvents(Keyboard& keyboard, Cursor& cursor);
    void handleSceneTilesEvents(Keyboard& keyboard, Cursor& cursor);

    void doButtonMouseOver(Cursor& cursor, std::shared_ptr<ButtonTile> button);
    void doButtonMouseOut(Cursor& cursor, std::shared_ptr<ButtonTile> button);
    void doButtonMouseClick(Cursor& cursor, std::shared_ptr<ButtonTile> button);

    void createDynamicTileSnappedToCursor(Cursor &cursor, std::shared_ptr<ButtonTile> button);

    void performLongClickDrop(Cursor &cursor);
    void performQuickClickDrop(Cursor &cursor);

    void performHover(Cursor &cursor, std::shared_ptr<DynamicTile> &tile);
    void performDragDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile);
    void performDrop(Cursor &cursor, std::shared_ptr<DynamicTile> &tile);
    void cancelDragging(Cursor& cursor);
};
