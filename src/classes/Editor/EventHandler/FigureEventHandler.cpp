#include "FigureEventHandler.hpp"

#include "classes/Editor/ObjectRegistry.hpp"

FigureEventHandler::FigureEventHandler(std::shared_ptr<AnimationPerformer> animationPerformer) {
    this->animationPerformer = animationPerformer;
}

void FigureEventHandler::handleEvents(Keyboard &keyboard, Cursor &cursor) {
    auto figures = ObjectRegistry::getFigures();

    for (auto &figure : figures) {
        performHover(cursor, figure);
    }
}

void FigureEventHandler::performHover(Cursor &cursor, std::shared_ptr<Figure> &figure) {
    auto highlightedTiles = ObjectRegistry::getHighlightedTiles();

//    if (highlightedTiles.empty()) {
//        if (cursor.isOver(figure) && !cursor.isOverRegistered(figure)) {
//            cursor.registerOver(figure);
//            figure->mouseEnter(animationPerformer);
//        } else if (cursor.isOver(figure)) {
//            figure->mouseOver(animationPerformer);
//        }
//    } else if (!cursor.isOver(figure) && cursor.isOverRegistered(figure)) {
//        cursor.unregisterOver(figure);
//        figure->mouseLeave(animationPerformer);
//    }
}
