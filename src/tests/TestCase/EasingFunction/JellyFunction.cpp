#include <gtest/gtest.h>

#include "classes/EasingFunction/JellyFunction.hpp"

JellyFunction createJellyPositiveToPositiveFunction() {
    JellyFunction function(1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.0018882f, function.getValue(0));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.7139454f, function.getValue(375));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0206118f, function.getValue(750));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.2f, function.getValue(1125));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_76percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.1737561f, function.getValue(1140));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_80percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.1559f, function.getValue(1200));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_90percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0911f, function.getValue(1350));
}

TEST(EasingFunction_JellyFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createJellyPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.9974999f, function.getValue(1500));
}