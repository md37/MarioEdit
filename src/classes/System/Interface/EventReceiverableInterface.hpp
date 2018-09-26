#pragma once

#include "classes/System/Keyboard.hpp"
#include "classes/System/Cursor.hpp"

class EventReceiverableInterface {

public:

    virtual void handleEvents(Keyboard& keyboard, Cursor& cursor)=0;

};