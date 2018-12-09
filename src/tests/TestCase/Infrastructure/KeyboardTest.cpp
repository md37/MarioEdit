#include <gtest/gtest.h>

#include "classes/Infrastructure/Keyboard.hpp"

TEST(KeyboardTest, test_not_pressed) {
    Keyboard keyboard;
    ASSERT_FALSE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_pressed) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    ASSERT_TRUE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_pressed_two_times) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    keyboard.press(sf::Keyboard::Key::Space);
    ASSERT_TRUE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_released) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    keyboard.release(sf::Keyboard::Key::Space);
    ASSERT_FALSE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_released_two_times) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    keyboard.release(sf::Keyboard::Key::Space);
    keyboard.release(sf::Keyboard::Key::Space);
    ASSERT_FALSE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_no_numeric_key_pressed) {
    Keyboard keyboard;
    ASSERT_FALSE(keyboard.isNumericKeyPressed());
    ASSERT_FALSE(keyboard.getPressedNumeric().has_value());
}

TEST(KeyboardTest, test_numeric_key_0_is_pressed) {
    sf::Keyboard::Key keys[10] = {
        sf::Keyboard::Key::Num0, sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num2, sf::Keyboard::Key::Num3,
        sf::Keyboard::Key::Num4, sf::Keyboard::Key::Num5, sf::Keyboard::Key::Num6, sf::Keyboard::Key::Num7,
        sf::Keyboard::Key::Num8, sf::Keyboard::Key::Num9
    };

    for (auto key: keys) {
        Keyboard keyboard;
        keyboard.press(key);
        ASSERT_TRUE(keyboard.isNumericKeyPressed());
        ASSERT_TRUE(keyboard.getPressedNumeric().has_value());
    }
}