#include <gtest/gtest.h>

#include "classes/EasingFunction/QuadraticFunction.hpp"

QuadraticFunction createQuadraticPositiveToPositiveFunction() {
    QuadraticFunction function(1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_QuadraticFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createQuadraticPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.0f, function.getValue(0));
}

TEST(EasingFunction_QuadraticFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createQuadraticPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.0625f, function.getValue(375));
}

TEST(EasingFunction_QuadraticFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createQuadraticPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.25f, function.getValue(750));
}

TEST(EasingFunction_QuadraticFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createQuadraticPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.5625f, function.getValue(1125));
}

TEST(EasingFunction_QuadraticFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createQuadraticPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

QuadraticFunction createQuadraticNegativeToPositiveFunction() {
    QuadraticFunction function(1500, -2.0f, 2.0f);
    return function;
}

TEST(EasingFunction_QuadraticFunction_NegativeToPositive_Test, test_0percent_value) {
    auto function = createQuadraticNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(-2.0f, function.getValue(0));
}

TEST(EasingFunction_QuadraticFunction_NegativeToPositive_Test, test_25percent_value) {
    auto function = createQuadraticNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(-1.75f, function.getValue(375));
}

TEST(EasingFunction_QuadraticFunction_NegativeToPositive_Test, test_50percent_value) {
    auto function = createQuadraticNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(-1.0f, function.getValue(750));
}

TEST(EasingFunction_QuadraticFunction_NegativeToPositive_Test, test_75percent_value) {
    auto function = createQuadraticNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(0.25f, function.getValue(1125));
}

TEST(EasingFunction_QuadraticFunction_NegativeToPositive_Test, test_100percent_value) {
    auto function = createQuadraticNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

QuadraticFunction createQuadraticNegativeToNegativeFunction() {
    QuadraticFunction function(1500, -4.0f, -2.0f);
    return function;
}

TEST(EasingFunction_QuadraticFunction_NegativeToNegative_Test, test_0percent_value) {
    auto function = createQuadraticNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-4.0f, function.getValue(0));
}

TEST(EasingFunction_QuadraticFunction_NegativeToNegative_Test, test_25percent_value) {
    auto function = createQuadraticNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-3.875f, function.getValue(375));
}

TEST(EasingFunction_QuadraticFunction_NegativeToNegative_Test, test_50percent_value) {
    auto function = createQuadraticNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-3.5f, function.getValue(750));
}

TEST(EasingFunction_QuadraticFunction_NegativeToNegative_Test, test_75percent_value) {
    auto function = createQuadraticNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-2.875f, function.getValue(1125));
}

TEST(EasingFunction_QuadraticFunction_NegativeToNegative_Test, test_100percent_value) {
    auto function = createQuadraticNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-2.0f, function.getValue(1500));
}