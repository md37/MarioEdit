#pragma once

#include <memory>
#include <vector>
#include "classes/System/Animation/Animation.hpp"
#include "classes/System/Interface/RunnableInterface.hpp"

class AnimationPerformer : public RunnableInterface {

public:

    void start() override;
    bool isStarted() override;

    void add(std::shared_ptr<Animation> animation);
    void remove(std::shared_ptr<Animation> animation);
    void process();

private:

    bool isStartedFlag = false;
    std::vector<std::shared_ptr<Animation>> animations;

};
