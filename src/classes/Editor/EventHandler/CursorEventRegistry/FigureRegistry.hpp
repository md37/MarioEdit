#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class FigureEventRegistry {

public:

    void registerOver(std::shared_ptr<Figure> figure);
    void unregisterOver(std::shared_ptr<Figure> figure);
    bool isOverRegistered(std::shared_ptr<Figure> figure);

    void registerDrag(std::shared_ptr<Figure> figure);
    void unregisterDrag(std::shared_ptr<Figure> figure);
    bool isDragRegistered(std::shared_ptr<Figure> figure);

    std::vector<std::shared_ptr<Figure>> getRegisteredDragOnFigures();

private:

    std::vector<std::shared_ptr<Figure>> registeredOverOnFigures;
    std::vector<std::shared_ptr<Figure>> registeredDragOnFigures;

};
