#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>
#include "classes/System/Resolution.hpp"


TEST(ResolutionTest, test_max_resolution) {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (auto mode : modes) {
        if (mode.height > maxHeightMode.height) {
            maxHeightMode = mode;
        }
    }

    Resolution resolution;
    ASSERT_EQ(resolution.findHighestResolutionMode(), maxHeightMode);
}