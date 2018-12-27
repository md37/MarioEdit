#include "DragVisitator.hpp"

#include "classes/Editor/Scene/Figure/DynamicFigure.hpp"

DragVisitator::DragVisitator(Cursor &cursor): cursor(cursor) {

}

void DragVisitator::operator()(std::shared_ptr<DynamicTile>& tile) {
    tile->drag(cursor.getPosition());
}

void DragVisitator::operator()(std::shared_ptr<DynamicFigure>& figure) {
    figure->drag(cursor.getPosition());
}