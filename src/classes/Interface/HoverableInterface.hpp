#pragma once

class HoverableInterface {

public:

    virtual void mouseEnter()=0;
    virtual void mouseOver()=0;
    virtual void mouseLeave()=0;

    virtual bool isMouseOver()=0;

};