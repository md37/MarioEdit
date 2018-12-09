#pragma once

#include "classes/Infrastructure/Interface/RunnableInterface.hpp"
#include "classes/Infrastructure/Interface/EventReceiverableInterface.hpp"

class Game : public RunnableInterface, public EventReceiverableInterface {

public:

    void start() override;
    bool isStarted() const override;

    void handleEvents(Keyboard& keyboard, Cursor& cursor) override;

private:

    bool isStartedFlag = false;

};
