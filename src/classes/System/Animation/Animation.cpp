#include "Animation.hpp"

Animation::Animation(sf::Uint32 duration, bool isRepeatingFlag) {
    this->duration = duration;
    this->isRepeatingFlag = isRepeatingFlag;
    clock.restart();
    startMilliseconds = clock.getElapsedTime().asMilliseconds();
}

bool Animation::isFinished() {
    if (isStopped) {
        return true;
    }
    return getAnimationPointInTime() == duration && !isRepeatingFlag;
}

void Animation::stop() {
    isStopped = true;
}

sf::Int32 Animation::getAnimationPointInTime() const {
    sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
    sf::Int32 animationPointInTime = currentMilliseconds - startMilliseconds;
    if (animationPointInTime > duration) {
        animationPointInTime = duration;
    }
    return animationPointInTime;
}

void Animation::setStartCallback(std::function<void()> callback) {
    startCallback = callback;
}

void Animation::runStartCallback() {
    if (startCallback == nullptr) {
        return;
    }
    startCallback();
}


void Animation::setFinishCallback(std::function<void()> callback) {
    finishCallback = callback;
}

void Animation::runFinishCallback() {
    if (finishCallback == nullptr) {
        return;
    }
    finishCallback();
}
