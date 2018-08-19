#include <gtest/gtest.h>

#include "classes/EasingFunction/LogarithmFunction.hpp"

LogarithmFunction createLogarithmPositiveToPositiveFunction() {
    LogarithmFunction function(1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_LogarithmFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createLogarithmPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.0014225f, function.getValue(0));
}

TEST(EasingFunction_LogarithmFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createLogarithmPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.5379019f, function.getValue(375));
}

TEST(EasingFunction_LogarithmFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createLogarithmPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.7689509f, function.getValue(750));
}

TEST(EasingFunction_LogarithmFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createLogarithmPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(1.9041059f, function.getValue(1125));
}

TEST(EasingFunction_LogarithmFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createLogarithmPositiveToPositiveFunction();
    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}