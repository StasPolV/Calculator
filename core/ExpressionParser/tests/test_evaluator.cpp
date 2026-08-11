#include "Evaluator.h"
#include "ExpressionError.h"

#include <gtest/gtest.h>

namespace
{
	std::unique_ptr<Node> MakeNumber(double value)
	{
		auto node = std::make_unique<Node>();
		node->type = TokenType::NUMBER;
		node->value = value;
		return node;
	}

	std::unique_ptr<Node> MakeBinary(TokenType type, std::unique_ptr<Node> left,
	                                 std::unique_ptr<Node> right)
	{
		auto node = std::make_unique<Node>();
		node->type = type;
		node->left = std::move(left);
		node->right = std::move(right);
		return node;
	}

	std::unique_ptr<Node> MakeUnary(TokenType type, std::unique_ptr<Node> operand)
	{
		auto node = std::make_unique<Node>();
		node->type = type;
		node->right = std::move(operand);
		return node;
	}
}  // namespace

TEST(EvaluatorTest, EvaluatesNumberLiteral)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeNumber(42.0));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 42.0);
}

TEST(EvaluatorTest, EvaluatesAddition)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeBinary(TokenType::PLUS, MakeNumber(3), MakeNumber(4)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 7.0);
}

TEST(EvaluatorTest, EvaluatesSubtraction)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeBinary(TokenType::MINUS, MakeNumber(10), MakeNumber(4)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 6.0);
}

TEST(EvaluatorTest, EvaluatesMultiplication)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeBinary(TokenType::MULTIPLICATION, MakeNumber(3), MakeNumber(5)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 15.0);
}

TEST(EvaluatorTest, EvaluatesDivision)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeBinary(TokenType::DIVISION, MakeNumber(10), MakeNumber(4)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 2.5);
}

TEST(EvaluatorTest, ThrowsOnDivisionByZero)
{
	Evaluator evaluator;
	EXPECT_THROW(evaluator.Evaluate(MakeBinary(TokenType::DIVISION, MakeNumber(10), MakeNumber(0))),
	             ExpressionError);
}

TEST(EvaluatorTest, EvaluatesUnaryMinus)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeUnary(TokenType::UNARY_MINUS, MakeNumber(5)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), -5.0);
}

TEST(EvaluatorTest, EvaluatesPower)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeBinary(TokenType::POWER, MakeNumber(2), MakeNumber(10)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 1024.0);
}

TEST(EvaluatorTest, EvaluatesSqrt)
{
	Evaluator evaluator;
	evaluator.Evaluate(MakeUnary(TokenType::SQRT, MakeNumber(81)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 9.0);
}

TEST(EvaluatorTest, EvaluatesNestedExpressionTree)
{
	// (3 + 4) * 2
	Evaluator evaluator;
	auto sum = MakeBinary(TokenType::PLUS, MakeNumber(3), MakeNumber(4));
	evaluator.Evaluate(MakeBinary(TokenType::MULTIPLICATION, std::move(sum), MakeNumber(2)));
	EXPECT_DOUBLE_EQ(evaluator.GetResult(), 14.0);
}
