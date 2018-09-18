#include <gtest/gtest.h>

#include "classes/Animation/EasingFunction/BiasFunction.hpp"

BiasFunction createBiasPositiveToPositiveFunction() {
    BiasFunction function(0.8, 1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_BiasFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createBiasPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(0));
}

TEST(EasingFunction_BiasFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createBiasPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.6400001f, function.getValue(375));
}

TEST(EasingFunction_BiasFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createBiasPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.8f, function.getValue(750));
}

TEST(EasingFunction_BiasFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createBiasPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.9115462f, function.getValue(1125));
}

TEST(EasingFunction_BiasFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createBiasPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

BiasFunction createBiasNegativeToPositiveFunction() {
    BiasFunction function(0.8, 1500, -2.0f, 2.0f);
    return function;
}

TEST(EasingFunction_BiasFunction_NegativeToPositive_Test, test_0percent_value) {
    auto function = createBiasNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(0));
}

TEST(EasingFunction_BiasFunction_NegativeToPositive_Test, test_25percent_value) {
    auto function = createBiasNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(0.56000018f, function.getValue(375));
}

TEST(EasingFunction_BiasFunction_NegativeToPositive_Test, test_50percent_value) {
    auto function = createBiasNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(1.2f, function.getValue(750));
}

TEST(EasingFunction_BiasFunction_NegativeToPositive_Test, test_75percent_value) {
    auto function = createBiasNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(1.6461852f, function.getValue(1125));
}

TEST(EasingFunction_BiasFunction_NegativeToPositive_Test, test_100percent_value) {
    auto function = createBiasNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

BiasFunction createBiasNegativeToNegativeFunction() {
    BiasFunction function(0.8, 1500, -4.0f, -2.0f);
    return function;
}

TEST(EasingFunction_BiasFunction_NegativeToNegative_Test, test_0percent_value) {
    auto function = createBiasNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-4.0f, function.getValue(0));
}

TEST(EasingFunction_BiasFunction_NegativeToNegative_Test, test_25percent_value) {
    auto function = createBiasNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.7199998f, function.getValue(375));
}

TEST(EasingFunction_BiasFunction_NegativeToNegative_Test, test_50percent_value) {
    auto function = createBiasNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.4000001f, function.getValue(750));
}

TEST(EasingFunction_BiasFunction_NegativeToNegative_Test, test_75percent_value) {
    auto function = createBiasNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.1769075f, function.getValue(1125));
}

TEST(EasingFunction_BiasFunction_NegativeToNegative_Test, test_100percent_value) {
    auto function = createBiasNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(1500));
}

BiasFunction createBiasReversedFunction() {
    BiasFunction function(0.8, 1500, 2.0f, 1.0f);
    return function;
}

TEST(EasingFunction_BiasFunction_Reversed_Test, test_0percent_value) {
    auto function = createBiasReversedFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(0));
}

TEST(EasingFunction_BiasFunction_Reversed_Test, test_25percent_value) {
    auto function = createBiasReversedFunction();

    ASSERT_FLOAT_EQ(1.3599999f, function.getValue(375));
}

TEST(EasingFunction_BiasFunction_Reversed_Test, test_50percent_value) {
    auto function = createBiasReversedFunction();

    ASSERT_FLOAT_EQ(1.2f, function.getValue(750));
}

TEST(EasingFunction_BiasFunction_Reversed_Test, test_75percent_value) {
    auto function = createBiasReversedFunction();

    ASSERT_FLOAT_EQ(1.0884538f, function.getValue(1125));
}

TEST(EasingFunction_BiasFunction_Reversed_Test, test_100percent_value) {
    auto function = createBiasReversedFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(1500));
}