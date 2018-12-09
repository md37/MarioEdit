#include "DragVisitator.hpp"

#include "classes/Editor/Scene/Figure.hpp"
#include "classes/Editor/Scene/ResizeIndicator.hpp"

DragVisitator::DragVisitator(Cursor &cursor): cursor(cursor) {

}

void DragVisitator::operator()(std::shared_ptr<DynamicTile>& tile) {
    tile->drag(cursor.getPosition());
}

void DragVisitator::operator()(std::shared_ptr<Figure>& figure) {
    figure->drag(cursor.getPosition());
}

void DragVisitator::operator()(std::shared_ptr<ResizeIndicator>& indicator) {
    indicator->drag(cursor.getPosition());
}