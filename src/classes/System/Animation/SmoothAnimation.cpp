#include "SmoothAnimation.hpp"

bool SmoothAnimation::isRunning() {
    return isRunningFlag;
}

void SmoothAnimation::stop() {
    isStopped = true;
}
