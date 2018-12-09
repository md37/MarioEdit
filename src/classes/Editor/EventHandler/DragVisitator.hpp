#pragma once

#include "classes/Infrastructure/Cursor.hpp"

class Figure;
class ResizeIndicator;

class DragVisitator {

public:

    explicit DragVisitator(Cursor &cursor);

    void operator()(std::shared_ptr<DynamicTile>& tile);
    void operator()(std::shared_ptr<Figure>& figure);
    void operator()(std::shared_ptr<ResizeIndicator>& indicator);

private:

    Cursor &cursor;

};