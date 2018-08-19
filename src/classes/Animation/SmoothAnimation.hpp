#pragma once

#include <SFML/Config.hpp>

class SmoothAnimation {

public:

    bool isRunning();
    void stop();
    virtual void run()=0;

protected:

    bool isRunningFlag = false;
    bool isStopped = false;

    sf::Uint32 sleepTime = 10;
    sf::Uint32 duration = 1000;

    bool repeatable = false;
    bool stoppable = true;

};
