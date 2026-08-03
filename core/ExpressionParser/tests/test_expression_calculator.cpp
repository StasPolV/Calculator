#include <gtest/gtest.h>
#include "ExpressionCalculator.h"

TEST(ExpressionCalculatorTest, RespectsPrecedence) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.evaluate("3 + 4 * 2"), 11.0);
}

TEST(ExpressionCalculatorTest, RespectsParentheses) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.evaluate("(3 + 4) * 2"), 14.0);
}
