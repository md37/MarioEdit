#pragma once

#include <SFML/Config.hpp>

class SmoothAnimation {

public:

    virtual void run()=0;

protected:

    sf::Uint32  duration = 1000;

    bool repeatable = false;
    bool stoppable = true;

};
