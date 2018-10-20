#pragma once

#include "classes/System/Animation/AnimationPerformer.hpp"

class DraggableInterface {

public:

    virtual void startDrag(AnimationPerformer& animationPerformer)=0;
    virtual void drag()=0;
    virtual void drop(AnimationPerformer& animationPerformer)=0;

    virtual bool isDragging()=0;

};
