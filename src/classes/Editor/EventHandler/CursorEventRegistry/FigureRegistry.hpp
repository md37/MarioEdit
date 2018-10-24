#pragma once

#include "classes/Editor/Scene/Figure.hpp"

class FigureEventRegistry {

public:

    void registerOver(std::shared_ptr<Figure> figure);
    void unregisterOver(std::shared_ptr<Figure> figure);
    bool isOverRegistered(std::shared_ptr<Figure> figure);

private:

    std::vector<std::shared_ptr<Figure>> registeredOverOnFigures;

};
