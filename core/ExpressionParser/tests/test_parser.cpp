#include "ExpressionError.h"
#include "Parser.h"

#include <gtest/gtest.h>

namespace
{
	std::vector<Token> MakeTokens(std::initializer_list<Token> tokens)
	{
		return std::vector<Token>(tokens);
	}
}  // namespace

TEST(ParserTest, ParsesSingleNumber)
{
	Parser parser;
	parser.Parse(MakeTokens({
	        {TokenType::NUMBER,      "3"    },
            {TokenType::END_OF_LINE, "Empty"}
    }));

	auto root = parser.GetAstRoot();
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->type, TokenType::NUMBER);
	EXPECT_DOUBLE_EQ(root->value, 3.0);
}

TEST(ParserTest, BuildsBinaryNodeForAddition)
{
	Parser parser;
	parser.Parse(MakeTokens({
	        {TokenType::NUMBER,      "3"    },
	        {TokenType::PLUS,        "+"    },
	        {TokenType::NUMBER,      "4"    },
	        {TokenType::END_OF_LINE, "Empty"}
    }));

	auto root = parser.GetAstRoot();
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->type, TokenType::PLUS);
	ASSERT_NE(root->left, nullptr);
	ASSERT_NE(root->right, nullptr);
	EXPECT_DOUBLE_EQ(root->left->value, 3.0);
	EXPECT_DOUBLE_EQ(root->right->value, 4.0);
}

TEST(ParserTest, MultiplicationBindsTighterThanAddition)
{
	Parser parser;
	// 3 + 4 * 2  ->  root should be PLUS, whose right child is MULTIPLICATION
	parser.Parse(MakeTokens({
	        {TokenType::NUMBER,         "3"    },
	        {TokenType::PLUS,           "+"    },
	        {TokenType::NUMBER,         "4"    },
	        {TokenType::MULTIPLICATION, "*"    },
	        {TokenType::NUMBER,         "2"    },
	        {TokenType::END_OF_LINE,    "Empty"}
    }));

	auto root = parser.GetAstRoot();
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->type, TokenType::PLUS);
	ASSERT_NE(root->right, nullptr);
	EXPECT_EQ(root->right->type, TokenType::MULTIPLICATION);
}

TEST(ParserTest, LeadingMinusProducesUnaryMinusNode)
{
	Parser parser;
	parser.Parse(MakeTokens({
	        {TokenType::MINUS,       "-"    },
            {TokenType::NUMBER,      "5"    },
            {TokenType::END_OF_LINE, "Empty"}
    }));

	auto root = parser.GetAstRoot();
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->type, TokenType::UNARY_MINUS);
	ASSERT_NE(root->right, nullptr);
	EXPECT_DOUBLE_EQ(root->right->value, 5.0);
}

TEST(ParserTest, SqrtWrapsInnerExpression)
{
	Parser parser;
	parser.Parse(MakeTokens({
	        {TokenType::SQRT,        "sqrt" },
	        {TokenType::LPAREN,      "("    },
	        {TokenType::NUMBER,      "4"    },
	        {TokenType::RPAREN,      ")"    },
	        {TokenType::END_OF_LINE, "Empty"}
    }));

	auto root = parser.GetAstRoot();
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->type, TokenType::SQRT);
	ASSERT_NE(root->right, nullptr);
	EXPECT_DOUBLE_EQ(root->right->value, 4.0);
}

TEST(ParserTest, ThrowsOnTrailingTokenAfterExpression)
{
	Parser parser;
	EXPECT_THROW(parser.Parse(MakeTokens({
	                     {TokenType::NUMBER,      "3"    },
	                     {TokenType::NUMBER,      "4"    },
	                     {TokenType::END_OF_LINE, "Empty"}
    })),
	             ExpressionError);
}

TEST(ParserTest, ThrowsOnUnexpectedEndOfExpression)
{
	Parser parser;
	EXPECT_THROW(parser.Parse(MakeTokens({
	                     {TokenType::PLUS,        "+"    },
                         {TokenType::END_OF_LINE, "Empty"}
    })),
	             ExpressionError);
}

TEST(ParserTest, ThrowsOnUnclosedParenthesis)
{
	Parser parser;
	EXPECT_THROW(parser.Parse(MakeTokens({
	                     {TokenType::LPAREN,      "("    },
	                     {TokenType::NUMBER,      "3"    },
	                     {TokenType::END_OF_LINE, "Empty"}
    })),
	             ExpressionError);
}

TEST(ParserTest, ThrowsWhenSqrtNotFollowedByOpenParen)
{
	Parser parser;
	EXPECT_THROW(parser.Parse(MakeTokens({
	                     {TokenType::SQRT,        "sqrt" },
	                     {TokenType::NUMBER,      "4"    },
	                     {TokenType::END_OF_LINE, "Empty"}
    })),
	             ExpressionError);
}

TEST(ParserTest, ThrowsOnInvalidNumberLiteral)
{
	Parser parser;
	EXPECT_THROW(parser.Parse(MakeTokens({
	                     {TokenType::NUMBER,      "not-a-number"},
                         {TokenType::END_OF_LINE, "Empty"       }
    })),
	             ExpressionError);
}
