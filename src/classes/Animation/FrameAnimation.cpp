#include "FrameAnimation.hpp"

#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>

void FrameAnimation::run() {
    sf::Clock clock;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    thread = std::thread([=]() {
        while (true) {
            mutex.lock();
            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            sf::Int32 animationPointInTime = (currentMilliseconds-startMilliseconds) % duration;

            for (std::size_t i=0; i<frames.size(); i++) {
                if (frames.at(i)->entersNow(animationPointInTime, duration)) {
                    frames.at(i)->enter();
                }
            }
            mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    });
    thread.detach();
}

void FrameAnimation::addFrame(std::shared_ptr<Frame> frame) {
    frames.push_back(frame);
}