#include <gtest/gtest.h>

#include "tests/macros.hpp"
#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Resolution.hpp"

TEST(ResolutionTest, test_max_resolution) {
    SKIP_CI

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