#pragma once

#include "defines.hpp"

class EventRegistry {

public:

    void registerOver(HoverableItem item);
    void unregisterOver(HoverableItem item);
    bool isOverRegistered(HoverableItem item);

    void registerDrag(DraggableItem item);
    void unregisterDrag(DraggableItem item);
    bool isDragRegistered(DraggableItem item);

    std::vector<DraggableItem> getRegisteredDrags();

private:

    std::vector<HoverableItem> registeredOvers;
    std::vector<DraggableItem> registeredDrags;

};
