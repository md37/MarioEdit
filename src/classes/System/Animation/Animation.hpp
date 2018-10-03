#pragma once

#include <functional>
#include <SFML/Config.hpp>
#include <SFML/System/Clock.hpp>

class Animation {

public:

    Animation(sf::Uint32 duration, bool isRepeatingFlag);

    virtual void animate()=0;

    void stop();
    bool isFinished();

    void setStartCallback(std::function<void()> callback);
    void runStartCallback();

    void setFinishCallback(std::function<void()> callback);
    void runFinishCallback();

protected:

    sf::Clock clock;
    sf::Uint32 duration;
    sf::Int32 startMilliseconds;

    bool isStopped = false;
    bool isRepeatingFlag = false;

    std::function<void()> startCallback;
    std::function<void()> finishCallback;
    sf::Int32 getAnimationPointInTime() const;

};
