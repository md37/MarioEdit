#pragma once

class ClickableInterface {

public:

    virtual void clickLeft()=0;
    virtual void clickRight()=0;
    virtual void doubleClick()=0;

    virtual void isLeftClicked()=0;
    virtual void isRightClicked()=0;
    virtual void isDoubleClick()=0;
};
