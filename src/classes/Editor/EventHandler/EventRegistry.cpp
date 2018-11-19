#include "EventRegistry.hpp"

void EventRegistry::registerOver(HoverableItem item) {
    if (!isOverRegistered(item)) {
        registeredOvers.push_back(item);
    }
}

void EventRegistry::unregisterOver(HoverableItem item) {
    if (isOverRegistered(item)) {
        registeredOvers.erase(
            std::remove(registeredOvers.begin(), registeredOvers.end(), item), registeredOvers.end()
        );
    }
}

bool EventRegistry::isOverRegistered(HoverableItem item) {
    if (registeredOvers.empty()) {
        return false;
    }

    return std::find(registeredOvers.begin(), registeredOvers.end(), item) != registeredOvers.end();
}

void EventRegistry::registerDrag(DraggableItem item) {
    if (!isDragRegistered(item)) {
        registeredDrags.push_back(item);
    }
}

void EventRegistry::unregisterDrag(DraggableItem item) {
    if (isDragRegistered(item)) {
        registeredDrags.erase(
                std::remove(registeredDrags.begin(), registeredDrags.end(), item), registeredDrags.end()
        );
    }
}

bool EventRegistry::isDragRegistered(DraggableItem item) {
    if (registeredDrags.empty()) {
        return false;
    }

    return std::find(registeredDrags.begin(), registeredDrags.end(), item) != registeredDrags.end();
}

std::vector<DraggableItem> EventRegistry::getRegisteredDrags() {
    return registeredDrags;
}
