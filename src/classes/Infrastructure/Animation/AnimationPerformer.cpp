#include "AnimationPerformer.hpp"

#include "classes/Editor/Scene/Animation/SpecialBlockBlinkAnimation.hpp"

void AnimationPerformer::start() {
    add(std::make_shared<SpecialBlockBlinkAnimation>());
    isStartedFlag = true;
}

bool AnimationPerformer::isStarted() const {
    return isStartedFlag;
}

void AnimationPerformer::add(std::shared_ptr<Animation> animation) {
    animation->runStartCallback();
    animations.push_back(animation);
}

void AnimationPerformer::process() {
    for (auto it=animations.begin(); it != animations.end();) {
        (*it)->animate();
        if ((*it)->isFinished()) {
            remove(it);
            continue;
        }
        it++;
    }
}

void AnimationPerformer::remove(std::vector<std::shared_ptr<Animation>>::iterator& animationIterator) {
    (*animationIterator)->runFinishCallback();
    animationIterator = animations.erase(animationIterator);
}
