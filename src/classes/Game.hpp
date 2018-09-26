#pragma once

#include "classes/System/Interface/RunnableInterface.hpp"
#include "classes/System/Interface/EventReceiverableInterface.hpp"

class Game : public RunnableInterface, public EventReceiverableInterface {

public:

    void start() override;
    bool isStarted() override;

    void handleEvents(Keyboard& keyboard, Cursor& cursor) override;

private:

    bool isStartedFlag = false;

};
