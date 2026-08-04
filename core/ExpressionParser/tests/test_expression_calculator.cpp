#include <gtest/gtest.h>
#include "ExpressionCalculator.h"

TEST(ExpressionCalculatorTest, RespectsPrecedence) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("3 + 4 * 2"), 11.0);
}

TEST(ExpressionCalculatorTest, RespectsParentheses) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("(3 + 4) * 2"), 14.0);
}

TEST(ExpressionCalculatorTest, LeadingUnaryMinus) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("-5"), -5.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusInParentheses) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("2 * (-5)"), -10.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusAfterMultiplication) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("3 * -5"), -15.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusAfterDivision) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("10 / -2"), -5.0);
}

TEST(ExpressionCalculatorTest, DoubleNegation) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("5 - -3"), 8.0);
}

TEST(ExpressionCalculatorTest, TripleNegation) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("5 - - -3"), 2.0);
}

TEST(ExpressionCalculatorTest, UnaryPlusIsNoOp) {
    ExpressionCalculator calc;
    EXPECT_DOUBLE_EQ(calc.Evaluate("+5"), 5.0);
}
