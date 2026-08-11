#include "ExpressionError.h"
#include "Tokenizer.h"

#include <gtest/gtest.h>

TEST(TokenizerTest, TokenizesSingleNumber)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("42");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 2u);
	EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
	EXPECT_EQ(tokens[0].value, "42");
	EXPECT_EQ(tokens[1].type, TokenType::END_OF_LINE);
}

TEST(TokenizerTest, TokenizesDecimalNumber)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("3.14");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 2u);
	EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
	EXPECT_EQ(tokens[0].value, "3.14");
}

TEST(TokenizerTest, TokenizesAllSymbolOperators)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("(+-*/^)");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 8u);
	EXPECT_EQ(tokens[0].type, TokenType::LPAREN);
	EXPECT_EQ(tokens[1].type, TokenType::PLUS);
	EXPECT_EQ(tokens[2].type, TokenType::MINUS);
	EXPECT_EQ(tokens[3].type, TokenType::MULTIPLICATION);
	EXPECT_EQ(tokens[4].type, TokenType::DIVISION);
	EXPECT_EQ(tokens[5].type, TokenType::POWER);
	EXPECT_EQ(tokens[6].type, TokenType::RPAREN);
	EXPECT_EQ(tokens[7].type, TokenType::END_OF_LINE);
}

TEST(TokenizerTest, RecognizesSqrtIdentifier)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("sqrt(4)");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 5u);
	EXPECT_EQ(tokens[0].type, TokenType::SQRT);
	EXPECT_EQ(tokens[0].value, "sqrt");
}

TEST(TokenizerTest, SkipsWhitespaceBetweenTokens)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("  3   +   4  ");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 4u);
	EXPECT_EQ(tokens[0].value, "3");
	EXPECT_EQ(tokens[1].type, TokenType::PLUS);
	EXPECT_EQ(tokens[2].value, "4");
}

TEST(TokenizerTest, ThrowsOnUnknownIdentifier)
{
	Tokenizer tokenizer;
	EXPECT_THROW(tokenizer.Tokenize("foo(1)"), ExpressionError);
}

TEST(TokenizerTest, ThrowsOnUnknownSymbol)
{
	Tokenizer tokenizer;
	EXPECT_THROW(tokenizer.Tokenize("3 & 4"), ExpressionError);
}

TEST(TokenizerTest, EmptyExpressionProducesOnlyEndOfLine)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 1u);
	EXPECT_EQ(tokens[0].type, TokenType::END_OF_LINE);
}

TEST(TokenizerTest, RepeatedTokenizeCallsResetState)
{
	Tokenizer tokenizer;
	tokenizer.Tokenize("1 + 2 + 3");
	tokenizer.Tokenize("9");

	const auto& tokens = tokenizer.GetTokens();
	ASSERT_EQ(tokens.size(), 2u);
	EXPECT_EQ(tokens[0].value, "9");
}
