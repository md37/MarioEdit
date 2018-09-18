#include <gtest/gtest.h>

#include "classes/Animation/EasingFunction/GammaFunction.hpp"

GammaFunction createGammaPositiveToPositiveFunction() {
    GammaFunction function(2.3, 1500, 1.0f, 2.0f);
    return function;
}

TEST(EasingFunction_GammaFunction_PositiveToPositive_Test, test_0percent_value) {
    auto function = createGammaPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(0));
}

TEST(EasingFunction_GammaFunction_PositiveToPositive_Test, test_25percent_value) {
    auto function = createGammaPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.5473118f, function.getValue(375));
}

TEST(EasingFunction_GammaFunction_PositiveToPositive_Test, test_50percent_value) {
    auto function = createGammaPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.7398052f, function.getValue(750));
}

TEST(EasingFunction_GammaFunction_PositiveToPositive_Test, test_75percent_value) {
    auto function = createGammaPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(1.882427f, function.getValue(1125));
}

TEST(EasingFunction_GammaFunction_PositiveToPositive_Test, test_100percent_value) {
    auto function = createGammaPositiveToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

GammaFunction createGammaNegativeToPositiveFunction() {
    GammaFunction function(2.3, 1500, -2.0f, 2.0f);
    return function;
}

TEST(EasingFunction_GammaFunction_NegativeToPositive_Test, test_0percent_value) {
    auto function = createGammaNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(0));
}

TEST(EasingFunction_GammaFunction_NegativeToPositive_Test, test_25percent_value) {
    auto function = createGammaNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(0.18924713f, function.getValue(375));
}

TEST(EasingFunction_GammaFunction_NegativeToPositive_Test, test_50percent_value) {
    auto function = createGammaNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(0.95922089f, function.getValue(750));
}

TEST(EasingFunction_GammaFunction_NegativeToPositive_Test, test_75percent_value) {
    auto function = createGammaNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(1.5297081f, function.getValue(1125));
}

TEST(EasingFunction_GammaFunction_NegativeToPositive_Test, test_100percent_value) {
    auto function = createGammaNegativeToPositiveFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(1500));
}

GammaFunction createGammaNegativeToNegativeFunction() {
    GammaFunction function(2.3, 1500, -4.0f, -2.0f);
    return function;
}

TEST(EasingFunction_GammaFunction_NegativeToNegative_Test, test_0percent_value) {
    auto function = createGammaNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-4.0f, function.getValue(0));
}

TEST(EasingFunction_GammaFunction_NegativeToNegative_Test, test_25percent_value) {
    auto function = createGammaNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.9053764f, function.getValue(375));
}

TEST(EasingFunction_GammaFunction_NegativeToNegative_Test, test_50percent_value) {
    auto function = createGammaNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.5203896f, function.getValue(750));
}

TEST(EasingFunction_GammaFunction_NegativeToNegative_Test, test_75percent_value) {
    auto function = createGammaNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.235146f, function.getValue(1125));
}

TEST(EasingFunction_GammaFunction_NegativeToNegative_Test, test_100percent_value) {
    auto function = createGammaNegativeToNegativeFunction();

    ASSERT_FLOAT_EQ(-2.0f, function.getValue(1500));
}

GammaFunction createGammaReversedFunction() {
    GammaFunction function(2.3, 1500, 2.0f, 1.0f);
    return function;
}

TEST(EasingFunction_GammaFunction_Reversed_Test, test_0percent_value) {
    auto function = createGammaReversedFunction();

    ASSERT_FLOAT_EQ(2.0f, function.getValue(0));
}

TEST(EasingFunction_GammaFunction_Reversed_Test, test_25percent_value) {
    auto function = createGammaReversedFunction();

    ASSERT_FLOAT_EQ(1.4526882f, function.getValue(375));
}

TEST(EasingFunction_GammaFunction_Reversed_Test, test_50percent_value) {
    auto function = createGammaReversedFunction();

    ASSERT_FLOAT_EQ(1.2601948f, function.getValue(750));
}

TEST(EasingFunction_GammaFunction_Reversed_Test, test_75percent_value) {
    auto function = createGammaReversedFunction();

    ASSERT_FLOAT_EQ(1.117573f, function.getValue(1125));
}

TEST(EasingFunction_GammaFunction_Reversed_Test, test_100percent_value) {
    auto function = createGammaReversedFunction();

    ASSERT_FLOAT_EQ(1.0f, function.getValue(1500));
}