#include "DragVisitator.hpp"

#include "classes/Editor/Scene/Figure.hpp"

DragVisitator::DragVisitator(Cursor &cursor): cursor(cursor) {

}

void DragVisitator::operator()(std::shared_ptr<DynamicTile>& tile) {
    tile->drag(cursor.getPosition());
}

void DragVisitator::operator()(std::shared_ptr<Figure>& figure) {
    figure->drag(cursor.getPosition());
}