#pragma once

#include "classes/System/Animation/AnimationPerformer.hpp"

class DraggableInterface {

public:

    virtual void startDrag(std::shared_ptr<AnimationPerformer> animationPerformer)=0;
    virtual void drag()=0;
    virtual void drop(std::shared_ptr<AnimationPerformer> animationPerformer)=0;

    virtual bool isDragging()=0;

};
