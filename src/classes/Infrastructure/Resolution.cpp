#include "Resolution.hpp"

sf::VideoMode Resolution::findHighestResolutionMode() {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (auto mode : modes) {
        if (mode.height > maxHeightMode.height) {
            maxHeightMode = mode;
        }
    }
    return maxHeightMode;
}
