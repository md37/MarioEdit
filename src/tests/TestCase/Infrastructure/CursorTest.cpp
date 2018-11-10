#include <gtest/gtest.h>

#include "classes/Infrastructure/Cursor.hpp"

TEST(CursorTest, test_click_default_value) {
    Cursor cursor;
    EXPECT_FALSE(cursor.isClick());
}

TEST(CursorTest, test_click_true) {
    Cursor cursor;
    cursor.click(true, sf::Mouse::Button::Left);
    EXPECT_TRUE(cursor.isClick());
}

TEST(CursorTest, test_click_false) {
    Cursor cursor;
    cursor.click(false, sf::Mouse::Button::Left);
    EXPECT_FALSE(cursor.isClick());
}

TEST(CursorTest, test_click_default_type) {
    Cursor cursor;
    EXPECT_EQ(sf::Mouse::Button::Left, cursor.getClickType());
}

TEST(CursorTest, test_click_type_changes_on_true) {
    Cursor cursor;
    cursor.click(true, sf::Mouse::Button::Right);
    EXPECT_EQ(sf::Mouse::Button::Right, cursor.getClickType());
}

TEST(CursorTest, test_click_type_not_changes_on_false) {
    Cursor cursor;
    cursor.click(false, sf::Mouse::Button::Right);
    EXPECT_EQ(sf::Mouse::Button::Right, cursor.getClickType());
}

TEST(CursorTest, test_default_position) {
    Cursor cursor;
    EXPECT_EQ(sf::Vector2f(0, 0), cursor.getPosition());
}

TEST(CursorTest, test_change_position) {
    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(30, 50));
    EXPECT_EQ(sf::Vector2f(30, 50), cursor.getPosition());
}

TEST(CursorTest, test_mouse_move_default_value) {
    Cursor cursor;
    EXPECT_FALSE(cursor.isMouseMoved());
}

TEST(CursorTest, test_mouse_move) {
    Cursor cursor;
    cursor.mouseMove(true);
    EXPECT_TRUE(cursor.isMouseMoved());

    cursor.mouseMove(false);
    EXPECT_FALSE(cursor.isMouseMoved());
}

TEST(CursorTest, test_mouse_default_press_duration) {
    Cursor cursor;
    cursor.mousePress(true);
    EXPECT_LE(0.0f, cursor.getClickDuration().asMilliseconds());
}

TEST(CursorTest, test_mouse_press_duration) {
    Cursor cursor;
    cursor.mousePress(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    EXPECT_LE(150.0f, cursor.getClickDuration().asMilliseconds());
}

TEST(CursorTest, test_mouse_long_click) {
    Cursor cursor;
    cursor.mousePress(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(152));
    EXPECT_TRUE(cursor.isLongClick());
}

TEST(CursorTest, test_mouse_not_long_click) {
    Cursor cursor;
    cursor.mousePress(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    EXPECT_FALSE(cursor.isLongClick());
}

TEST(CursorTest, test_reset_press_state) {
    Cursor cursor;
    cursor.mousePress(true);
    EXPECT_TRUE(cursor.isMousePressed());

    cursor.mouseRelease(true);
    EXPECT_TRUE(cursor.isMouseReleased());

    cursor.resetPressState();
    EXPECT_FALSE(cursor.isMousePressed());
    EXPECT_FALSE(cursor.isMouseReleased());
}

TEST(CursorTest, test_is_not_over_position_from_left) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(50, 150));

    EXPECT_FALSE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_not_over_position_from_top) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(150, 50));

    EXPECT_FALSE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_not_over_position_from_right) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(250, 150));

    EXPECT_FALSE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_not_over_position_from_bottom) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(150, 250);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(0, 0));

    EXPECT_FALSE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_bound_from_left) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(100, 150));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_bound_from_top) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(150, 100));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_bound_from_right) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(200, 150));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_bound_from_bottom) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(150, 200));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_from_left) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(102, 150));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_from_top) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(150, 102));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_from_right) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(198, 150));

    EXPECT_TRUE(cursor.isOver(position, size));
}

TEST(CursorTest, test_is_over_position_from_bottom) {
    sf::Vector2f position(100, 100);
    sf::Vector2u size(100, 100);

    Cursor cursor;
    cursor.updatePosition(sf::Vector2f(150, 198));

    EXPECT_TRUE(cursor.isOver(position, size));
}