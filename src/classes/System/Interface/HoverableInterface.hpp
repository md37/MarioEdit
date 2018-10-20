#pragma once

#include "classes/System/Animation/AnimationPerformer.hpp"

class HoverableInterface {

public:

    virtual void mouseEnter(AnimationPerformer& animationPerformer)=0;
    virtual void mouseOver(AnimationPerformer& animationPerformer)=0;
    virtual void mouseLeave(AnimationPerformer& animationPerformer)=0;

    virtual bool isMouseOver()=0;

};