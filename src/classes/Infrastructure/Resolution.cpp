#include "Resolution.hpp"

sf::VideoMode Resolution::findHighestResolutionMode() const {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (auto mode : modes) {
        if (mode.height > maxHeightMode.height) {
            maxHeightMode = mode;
        }
    }
    return maxHeightMode;
}
