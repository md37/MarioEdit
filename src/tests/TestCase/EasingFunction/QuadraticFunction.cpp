#include <gtest/gtest.h>

#include "classes/EasingFunction/QuadraticFunction.hpp"

QuadraticFunction createQuadraticPositiveToPositiveFunction() {
    QuadraticFunction function(1.0f, 1.0f, 0.0f);
    function.setDuration(1000);
    function.setMinValue(1.0f);
    function.setMaxValue(2.0f);
    return function;
}

TEST(EasingFunction_QuadraticFunction_PositiveToPositive_Test, test_min_value) {
    ASSERT_TRUE(false);
}