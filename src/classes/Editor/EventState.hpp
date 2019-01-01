#pragma once

#include "classes/Editor/Navigation/TileButton.hpp"

class EventState {

public:

    bool isDraggingNewTile = false;
    bool dismissTileDrop = false;
    bool clickedOnTileButton = false;
    std::shared_ptr<TileButton> lastUsedTileButton;

};
