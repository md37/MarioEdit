#include <gtest/gtest.h>

#include "classes/Editor/Scene/Grid.hpp"

sf::Vector2u windowSize(1280, 800);
auto scale = std::make_unique<Scale>(windowSize);
Grid grid(
    GridSettings(12, GridSettings::Auto, sf::Vector2f(GridSettings::Auto, GridSettings::Auto), sf::Vector2f(0, 0))
);

TEST(GridTest, test_size) {
    scale->change(windowSize);
    grid.rescale(scale);
    ASSERT_EQ(19, grid.getSize().x);
    ASSERT_EQ(12, grid.getSize().y);
}

TEST(GridTest, test_tile_0_0_point_on_top_left_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(0, 0);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_top_right_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(65, 0);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_bottom_right_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(65, 65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_bottom_left_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(0, 65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_left_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(0, 10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_right_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(65, 10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_top_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(10, 0);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_bottom_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(10, 65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_inside) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(10, 10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_top_left_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66, 66);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_top_right_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66+65, 66);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_bottom_right_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66+65, 66+65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_bottom_left_corner) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66, 66+65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_left_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66, 66+10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_right_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66+65, 66+10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_top_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66+10, 66);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_bottom_edge) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66+10, 66+65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_inside) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2f point(2*66+10, 66+10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_center_0_0) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2u pointOnGrid(0, 0);
    sf::Vector2f center = grid.getCenter(pointOnGrid);

    ASSERT_FLOAT_EQ(33.333332, center.x);
    ASSERT_FLOAT_EQ(-33.333332, center.y);
}

TEST(GridTest, test_center_2_1) {
    scale->change(windowSize);
    grid.rescale(scale);
    sf::Vector2u pointOnGrid(2, 1);
    sf::Vector2f center = grid.getCenter(pointOnGrid);

    ASSERT_FLOAT_EQ(166.66666, center.x);
    ASSERT_FLOAT_EQ(33.333332, center.y);
}