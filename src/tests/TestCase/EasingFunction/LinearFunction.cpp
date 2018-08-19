#include <gtest/gtest.h>

#include "classes/EasingFunction/LinearFunction.hpp"

LinearFunction createLinearPositiveToPositiveFunction() {
    LinearFunction function(1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_LinearFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createLinearPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(0));
}

TEST(EasingFunction_LinearFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createLinearPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.25f, function.getValue(375));
}

TEST(EasingFunction_LinearFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createLinearPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.5f, function.getValue(750));
}

TEST(EasingFunction_LinearFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createLinearPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

TEST(EasingFunction_LinearFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createLinearPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.75f, function.getValue(1125));
}

LinearFunction createLinearNegativeToPositiveFunction() {
    LinearFunction function(1500, -2.0f, 2.0f);
    return function;
}

TEST(EasingFunction_LinearFunction_NegativeToPositive_Test, test_0percent_value) {
    auto function = createLinearNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(0));
}

TEST(EasingFunction_LinearFunction_NegativeToPositive_Test, test_25percent_value) {
    auto function = createLinearNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(-1.0f, function.getValue(375));
}

TEST(EasingFunction_LinearFunction_NegativeToPositive_Test, test_50percent_value) {
    auto function = createLinearNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(0.0f, function.getValue(750));
}

TEST(EasingFunction_LinearFunction_NegativeToPositive_Test, test_75percent_value) {
    auto function = createLinearNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(1125));
}

TEST(EasingFunction_LinearFunction_NegativeToPositive_Test, test_100percent_value) {
    auto function = createLinearNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

LinearFunction createLinearNegativeToNegativeFunction() {
    LinearFunction function(1500, -4.0f, -2.0f);
    return function;
}

TEST(EasingFunction_LinearFunction_NegativeToNegative_Test, test_0percent_value) {
    auto function = createLinearNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-4.0f, function.getValue(0));
}

TEST(EasingFunction_LinearFunction_NegativeToNegative_Test, test_25percent_value) {
    auto function = createLinearNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-3.5f, function.getValue(375));
}

TEST(EasingFunction_LinearFunction_NegativeToNegative_Test, test_50percent_value) {
    auto function = createLinearNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-3.0f, function.getValue(750));
}

TEST(EasingFunction_LinearFunction_NegativeToNegative_Test, test_75percent_value) {
    auto function = createLinearNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.5f, function.getValue(1125));
}

TEST(EasingFunction_LinearFunction_NegativeToNegative_Test, test_100percent_value) {
    auto function = createLinearNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(1500));
}