#include "FigureRegistry.hpp"

void FigureEventRegistry::registerOver(std::shared_ptr<Figure> figure) {
    if (!isOverRegistered(figure)) {
        registeredOverOnFigures.push_back(figure);
    }
}

void FigureEventRegistry::unregisterOver(std::shared_ptr<Figure> figure) {
    if (isOverRegistered(figure)) {
        registeredOverOnFigures.erase(
            std::remove(registeredOverOnFigures.begin(), registeredOverOnFigures.end(), figure), registeredOverOnFigures.end()
        );
    }
}

bool FigureEventRegistry::isOverRegistered(std::shared_ptr<Figure> figure) {
    if (registeredOverOnFigures.empty()) {
        return false;
    }

    return std::find(registeredOverOnFigures.begin(), registeredOverOnFigures.end(), figure) != registeredOverOnFigures.end();
}

void FigureEventRegistry::registerDrag(std::shared_ptr<Figure> figure) {
    if (!isDragRegistered(figure)) {
        registeredDragOnFigures.push_back(figure);
    }
}

void FigureEventRegistry::unregisterDrag(std::shared_ptr<Figure> figure) {
    if (isDragRegistered(figure)) {
        registeredDragOnFigures.erase(
                std::remove(registeredDragOnFigures.begin(), registeredDragOnFigures.end(), figure), registeredDragOnFigures.end()
        );
    }
}

bool FigureEventRegistry::isDragRegistered(std::shared_ptr<Figure> figure) {
    if (registeredDragOnFigures.empty()) {
        return false;
    }

    return std::find(registeredDragOnFigures.begin(), registeredDragOnFigures.end(), figure) != registeredDragOnFigures.end();
}
