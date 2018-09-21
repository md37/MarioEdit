#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>
#include "classes/System/Scale.hpp"


TEST(ScaleTest, test_default_scale) {
    Scale scale;

    EXPECT_FLOAT_EQ(scale.getScale(), 1.0f);
    EXPECT_FLOAT_EQ(scale.getScaleRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_first_window_size) {
    Scale scale;
    scale.rescale(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(scale.getScale(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getScaleRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_two_window_sizes) {
    Scale scale;
    scale.rescale(sf::Vector2u(1280, 800));
    scale.rescale(sf::Vector2u(800, 600));

    EXPECT_FLOAT_EQ(scale.getScale(), 3.125);
    EXPECT_FLOAT_EQ(scale.getScaleRatio(), 0.75f);
}

TEST(ScaleTest, test_handle_width_rescalling) {
    Scale scale;
    scale.rescale(sf::Vector2u(1280, 800));
    scale.rescale(sf::Vector2u(800, 800));

    EXPECT_FLOAT_EQ(scale.getScale(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getScaleRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_height_rescalling) {
    Scale scale;
    scale.rescale(sf::Vector2u(1280, 800));
    scale.rescale(sf::Vector2u(1280, 600));

    EXPECT_FLOAT_EQ(scale.getScale(), 3.125);
    EXPECT_FLOAT_EQ(scale.getScaleRatio(), 0.75);
}

TEST(ScaleTest, test_handle_rescalling_to_same_dimensions) {
    Scale scale;
    scale.rescale(sf::Vector2u(1280, 800));
    scale.rescale(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(scale.getScale(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getScaleRatio(), 1.0f);
}