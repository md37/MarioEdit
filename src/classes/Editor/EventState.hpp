#pragma once

#include "classes/Editor/Navigation/TileButton.hpp"
#include "classes/Editor/Navigation/FigureButton.hpp"

class EventState {

public:

    bool isDraggingNewObject = false;
    bool dismissObjectDrop = false;
    bool clickedOnTileButton = false;
    std::shared_ptr<TileButton> lastUsedTileButton;
    std::shared_ptr<FigureButton> lastUsedFigureButton;

};
