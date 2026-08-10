#include "ExpressionCalculator.h"

#include <gtest/gtest.h>

TEST(ExpressionCalculatorTest, RespectsPrecedence)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("3 + 4 * 2"), 11.0);
}

TEST(ExpressionCalculatorTest, RespectsParentheses)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("(3 + 4) * 2"), 14.0);
}

TEST(ExpressionCalculatorTest, LeadingUnaryMinus)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("-5"), -5.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusInParentheses)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("2 * (-5)"), -10.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusAfterMultiplication)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("3 * -5"), -15.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusAfterDivision)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("10 / -2"), -5.0);
}

TEST(ExpressionCalculatorTest, DoubleNegation)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("5 - -3"), 8.0);
}

TEST(ExpressionCalculatorTest, TripleNegation)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("5 - - -3"), 2.0);
}

TEST(ExpressionCalculatorTest, UnaryPlusIsNoOp)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("+5"), 5.0);
}

TEST(ExpressionCalculatorTest, Square)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("4^2"), 16.0);
}

TEST(ExpressionCalculatorTest, PowerRightAssociative)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("2^3^2"), 512.0);
}

TEST(ExpressionCalculatorTest, PowerRespectsPrecedenceOverMultiplication)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("2*3^2"), 18.0);
}

TEST(ExpressionCalculatorTest, UnaryMinusAppliesAfterPower)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("-2^2"), -4.0);
}

TEST(ExpressionCalculatorTest, NegativeExponent)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("2^-2"), 0.25);
}

TEST(ExpressionCalculatorTest, SquareRoot)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("sqrt(16)"), 4.0);
}

TEST(ExpressionCalculatorTest, SquareRootOfExpression)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("sqrt(3+13)"), 4.0);
}

TEST(ExpressionCalculatorTest, ReciprocalNeedsNoGrammarChanges)
{
	ExpressionCalculator calc;
	EXPECT_DOUBLE_EQ(calc.Evaluate("1/5"), 0.2);
}
