#include "AnimationPerformer.hpp"

#include <iostream>

void AnimationPerformer::start() {
    isStartedFlag = true;
}

bool AnimationPerformer::isStarted() {
    return isStartedFlag;
}

void AnimationPerformer::add(std::shared_ptr<Animation> animation) {
    animation->runStartCallback();
    animations.push_back(animation);
}

void AnimationPerformer::process() {
    for (auto &animation: animations) {
        animation->animate();
    }
}

void AnimationPerformer::remove(std::shared_ptr<Animation> animation) {
    auto existingAnimation = std::find(animations.begin(), animations.end(), animation);
    if (existingAnimation == animations.end()) {
        return;
    }

    animation->runFinishCallback();
    animations.erase(existingAnimation, animations.end());
}
