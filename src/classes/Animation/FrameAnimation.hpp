#pragma once

#include <memory>
#include <vector>
#include <SFML/Config.hpp>
#include "FrameAnimation/Frame.hpp"

class FrameAnimation {

public:

    void run();

protected:

    sf::Uint32 sleepTime = 10;
    sf::Uint32 duration = 1000;
    std::vector<std::shared_ptr<Frame>> frames;

    void addFrame(std::shared_ptr<Frame> frame);

};
