#pragma once

#include "classes/Infrastructure/Animation/AnimationPerformer.hpp"

class HoverableInterface {

public:

    virtual void mouseEnter(std::unique_ptr<AnimationPerformer> &animationPerformer)=0;
    virtual void mouseOver(std::unique_ptr<AnimationPerformer> &animationPerformer)=0;
    virtual void mouseLeave(std::unique_ptr<AnimationPerformer> &animationPerformer)=0;

    virtual bool isMouseOver() const=0;

};