#include <gtest/gtest.h>

#include "classes/EasingFunction/GainFunction.hpp"

GainFunction createGainPositiveToPositiveFunction() {
    GainFunction function(0.2, 1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_GainFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createGainPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(0));
}

TEST(EasingFunction_GainFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createGainPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.4f, function.getValue(375));
}

TEST(EasingFunction_GainFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createGainPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.5f, function.getValue(750));
}

TEST(EasingFunction_GainFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createGainPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.6f, function.getValue(1125));
}

TEST(EasingFunction_GainFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createGainPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

GainFunction createGainNegativeToPositiveFunction() {
    GainFunction function(0.2, 1500, -2.0f, 2.0f);
    return function;
}

TEST(EasingFunction_GainFunction_NegativeToPositive_Test, test_0percent_value) {
    auto function = createGainNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(0));
}

TEST(EasingFunction_GainFunction_NegativeToPositive_Test, test_25percent_value) {
    auto function = createGainNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(-0.39999998f, function.getValue(375));
}

TEST(EasingFunction_GainFunction_NegativeToPositive_Test, test_50percent_value) {
    auto function = createGainNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(0.0f, function.getValue(750));
}

TEST(EasingFunction_GainFunction_NegativeToPositive_Test, test_75percent_value) {
    auto function = createGainNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(0.4000001f, function.getValue(1125));
}

TEST(EasingFunction_GainFunction_NegativeToPositive_Test, test_100percent_value) {
    auto function = createGainNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

GainFunction createGainNegativeToNegativeFunction() {
    GainFunction function(0.2, 1500, -4.0f, -2.0f);
    return function;
}

TEST(EasingFunction_GainFunction_NegativeToNegative_Test, test_0percent_value) {
    auto function = createGainNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-4.0f, function.getValue(0));
}

TEST(EasingFunction_GainFunction_NegativeToNegative_Test, test_25percent_value) {
    auto function = createGainNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-3.2f, function.getValue(375));
}

TEST(EasingFunction_GainFunction_NegativeToNegative_Test, test_50percent_value) {
    auto function = createGainNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-3.0f, function.getValue(750));
}

TEST(EasingFunction_GainFunction_NegativeToNegative_Test, test_75percent_value) {
    auto function = createGainNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.8f, function.getValue(1125));
}

TEST(EasingFunction_GainFunction_NegativeToNegative_Test, test_100percent_value) {
    auto function = createGainNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(1500));
}

GainFunction createGainReversedFunction() {
    GainFunction function(0.2, 1500, 2.0f, 1.0f);
    return function;
}

TEST(EasingFunction_GainFunction_Reversed_Test, test_0percent_value) {
    auto function = createGainReversedFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(0));
}

TEST(EasingFunction_GainFunction_Reversed_Test, test_25percent_value) {
    auto function = createGainReversedFunction();

    ASSERT_FLOAT_EQ(1.6f, function.getValue(375));
}

TEST(EasingFunction_GainFunction_Reversed_Test, test_50percent_value) {
    auto function = createGainReversedFunction();

    ASSERT_FLOAT_EQ(1.5f, function.getValue(750));
}

TEST(EasingFunction_GainFunction_Reversed_Test, test_75percent_value) {
    auto function = createGainReversedFunction();

    ASSERT_FLOAT_EQ(1.4f, function.getValue(1125));
}

TEST(EasingFunction_GainFunction_Reversed_Test, test_100percent_value) {
    auto function = createGainReversedFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(1500));
}