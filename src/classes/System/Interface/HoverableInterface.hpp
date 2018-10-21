#pragma once

#include "classes/System/Animation/AnimationPerformer.hpp"

class HoverableInterface {

public:

    virtual void mouseEnter(std::shared_ptr<AnimationPerformer> animationPerformer)=0;
    virtual void mouseOver(std::shared_ptr<AnimationPerformer> animationPerformer)=0;
    virtual void mouseLeave(std::shared_ptr<AnimationPerformer> animationPerformer)=0;

    virtual bool isMouseOver()=0;

};