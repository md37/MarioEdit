#include "AnimationPerformer.hpp"

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
        if (animation->isFinished()) {
            animation->runFinishCallback();
            this->removeAnimation(animation);
        }
    }
}

void AnimationPerformer::removeAnimation(std::shared_ptr<Animation> animation) {
    animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());
}
