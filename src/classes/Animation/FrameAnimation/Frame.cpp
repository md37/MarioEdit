#include "Frame.hpp"

Frame::Frame(sf::Uint32 leftBound, sf::Uint32 rightBound, std::function<void()> callback) {
    this->leftBound = leftBound;
    this->rightBound = rightBound;
    this->callback = callback;
}

bool Frame::entersNow(sf::Int32 animationPointInTime, sf::Int32 duration) {
    sf::Int32 currentPercent = (float)(animationPointInTime)/(float)(duration)*100;
    return currentPercent >= leftBound && currentPercent < rightBound;
}

void Frame::enter() {
    callback();
}