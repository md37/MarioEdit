#pragma once

#include "classes/Infrastructure/Cursor.hpp"

class DynamicFigure;

class DragVisitator {

public:

    explicit DragVisitator(Cursor &cursor);

    void operator()(std::shared_ptr<DynamicTile>& tile);
    void operator()(std::shared_ptr<DynamicFigure>& figure);

private:

    Cursor &cursor;

};