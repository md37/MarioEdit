#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <SFML/Config.hpp>
#include "classes/Animation/FrameAnimation/Frame.hpp"

class FrameAnimation {

public:

    void run();

protected:

    sf::Uint32 sleepTime = 100;
    sf::Uint32 duration = 1000;
    std::vector<std::shared_ptr<Frame>> frames;

    void addFrame(std::shared_ptr<Frame> frame);

    std::thread thread;
    std::mutex mutex;

};
