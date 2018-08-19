#include <gtest/gtest.h>

#include "classes/EasingFunction/LogarithmicFunction.hpp"

LogarithmicFunction createLogarithmicPositiveToPositiveFunction() {
    LogarithmicFunction function(1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_LogarithmicFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createLogarithmicPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.0014225f, function.getValue(0));
}

TEST(EasingFunction_LogarithmicFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createLogarithmicPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.5379019f, function.getValue(375));
}

TEST(EasingFunction_LogarithmicFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createLogarithmicPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.7689509f, function.getValue(750));
}

TEST(EasingFunction_LogarithmicFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createLogarithmicPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.9041059f, function.getValue(1125));
}

TEST(EasingFunction_LogarithmicFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createLogarithmicPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

LogarithmicFunction createLogarithmicNegativeToPositiveFunction() {
    LogarithmicFunction function(1500, -2.0f, 2.0f);
    return function;
}

TEST(EasingFunction_LogarithmicFunction_NegativeToPositive_Test, test_0percent_value) {
    auto function = createLogarithmicNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(-1.9943098f, function.getValue(0));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToPositive_Test, test_25percent_value) {
    auto function = createLogarithmicNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(0.15160751f, function.getValue(375));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToPositive_Test, test_50percent_value) {
    auto function = createLogarithmicNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(1.0758038f, function.getValue(750));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToPositive_Test, test_75percent_value) {
    auto function = createLogarithmicNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(1.6164238f, function.getValue(1125));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToPositive_Test, test_100percent_value) {
    auto function = createLogarithmicNegativeToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

LogarithmicFunction createLogarithmicNegativeToNegativeFunction() {
    LogarithmicFunction function(1500, -4.0f, -2.0f);
    return function;
}

TEST(EasingFunction_LogarithmicFunction_NegativeToNegative_Test, test_0percent_value) {
    auto function = createLogarithmicNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-3.997155f, function.getValue(0));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToNegative_Test, test_25percent_value) {
    auto function = createLogarithmicNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-2.9241962f, function.getValue(375));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToNegative_Test, test_50percent_value) {
    auto function = createLogarithmicNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-2.4620981f, function.getValue(750));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToNegative_Test, test_75percent_value) {
    auto function = createLogarithmicNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-2.1917882, function.getValue(1125));
}

TEST(EasingFunction_LogarithmicFunction_NegativeToNegative_Test, test_100percent_value) {
    auto function = createLogarithmicNegativeToNegativeFunction();
    ASSERT_FLOAT_EQ(-2.0f, function.getValue(1500));
}

LogarithmicFunction createLogarithmicReversedFunction() {
    LogarithmicFunction function(1500, 2.0f, 1.0f);
    return function;
}

TEST(EasingFunction_LogarithmicFunction_Reversed_Test, test_0percent_value) {
    auto function = createLogarithmicReversedFunction();
    ASSERT_FLOAT_EQ(1.9985775f, function.getValue(0));
}

TEST(EasingFunction_LogarithmicFunction_Reversed_Test, test_25percent_value) {
    auto function = createLogarithmicReversedFunction();
    ASSERT_FLOAT_EQ(1.4620981f, function.getValue(375));
}

TEST(EasingFunction_LogarithmicFunction_Reversed_Test, test_50percent_value) {
    auto function = createLogarithmicReversedFunction();
    ASSERT_FLOAT_EQ(1.2310491f, function.getValue(750));
}

TEST(EasingFunction_LogarithmicFunction_Reversed_Test, test_75percent_value) {
    auto function = createLogarithmicReversedFunction();
    ASSERT_FLOAT_EQ(1.0958941f, function.getValue(1125));
}

TEST(EasingFunction_LogarithmicFunction_Reversed_Test, test_100percent_value) {
    auto function = createLogarithmicReversedFunction();
    ASSERT_FLOAT_EQ(1.0f, function.getValue(1500));
}