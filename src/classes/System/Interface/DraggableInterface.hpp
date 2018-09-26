#pragma once

class DraggableInterface {

public:

    virtual void startDrag()=0;
    virtual void drag()=0;
    virtual void drop()=0;

    virtual bool isDragging()=0;

};
