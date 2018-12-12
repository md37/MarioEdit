#pragma once

class ClickableInterface {

public:

    virtual void clickLeft()=0;
    virtual void clickRight()=0;
    virtual void doubleClick()=0;

    virtual void isLeftClicked() const=0;
    virtual void isRightClicked() const=0;
    virtual void isDoubleClick() const=0;
};
