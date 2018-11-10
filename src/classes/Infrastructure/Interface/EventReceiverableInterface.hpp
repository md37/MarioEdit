#pragma once

#include "classes/Infrastructure/Keyboard.hpp"
#include "classes/Infrastructure/Cursor.hpp"

class EventReceiverableInterface {

public:

    virtual void handleEvents(Keyboard& keyboard, Cursor& cursor)=0;

};