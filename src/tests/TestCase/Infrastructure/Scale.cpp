#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>
#include "classes/Infrastructure/Scale.hpp"


TEST(ScaleTest, test_default_scale) {
    Scale scale(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_first_window_size) {
    Scale scale(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_two_window_sizes) {
    Scale scale(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(800, 600));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 3.125);
    EXPECT_FLOAT_EQ(scale.getRatio(), 0.75f);
}

TEST(ScaleTest, test_handle_width_rescalling) {
    Scale scale(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(800, 800));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_height_rescalling) {
    Scale scale(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 600));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 3.125);
    EXPECT_FLOAT_EQ(scale.getRatio(), 0.75);
}

TEST(ScaleTest, test_handle_rescalling_to_same_dimensions) {
    Scale scale(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 4.1666665);
    EXPECT_FLOAT_EQ(scale.getRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_two_times_rescalling) {
    Scale scale(sf::Vector2u(1280, 800));
    scale.change(sf::Vector2u(2560, 1600));
    scale.change(sf::Vector2u(640, 400));

    EXPECT_FLOAT_EQ(scale.getCurrent(), 2.0833333);
    EXPECT_FLOAT_EQ(scale.getRatio(), 0.25f);
}