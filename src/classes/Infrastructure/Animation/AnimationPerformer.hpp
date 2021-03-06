#pragma once

#include <memory>
#include <vector>
#include "classes/Infrastructure/Animation/Animation.hpp"
#include "classes/Infrastructure/Interface/RunnableInterface.hpp"

class AnimationPerformer : public RunnableInterface {

public:

    void start() override;
    bool isStarted() const override;

    void add(std::shared_ptr<Animation> animation);
    void remove(std::vector<std::shared_ptr<Animation>>::iterator& animationIterator);
    void process();

private:

    bool isStartedFlag = false;
    std::vector<std::shared_ptr<Animation>> animations;

};
