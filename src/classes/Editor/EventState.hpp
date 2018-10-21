#pragma once

#include "classes/Editor/Navigation/Tile/ButtonTile.hpp"

class EventState {

public:

    bool isDraggingNewTile = false;
    bool dismissTileDrop = false;
    bool clickedOnTileButton = false;
    std::shared_ptr<ButtonTile> lastUsedTileButton;

};
