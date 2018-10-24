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
