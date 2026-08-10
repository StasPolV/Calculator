#include "Parser.h"

#include "ExpressionError.h"

std::unique_ptr<Node> Parser::GetAstRoot()
{
	return std::move(m_ast_root);
}

bool Parser::IsAtEnd(const std::vector<Token>& tokens) const
{
	return m_index >= tokens.size();
}

const Token& Parser::Peek(const std::vector<Token>& tokens) const
{
	return tokens[m_index];
}

void Parser::Parse(const std::vector<Token>& tokens)
{
	m_index = 0;

	m_ast_root = ParseAdditive(tokens);

	if (!IsAtEnd(tokens) && Peek(tokens).type != TokenType::END_OF_LINE)
	{
		throw ExpressionError("Unexpected token '" + Peek(tokens).value +
		                      "' after end of expression");
	}
}

std::unique_ptr<Node> Parser::ParseAdditive(const std::vector<Token>& tokens)
{
	std::unique_ptr<Node> left = ParseMultiplication(tokens);

	while (!IsAtEnd(tokens) &&
	       (Peek(tokens).type == TokenType::PLUS || Peek(tokens).type == TokenType::MINUS))
	{
		TokenType op = Peek(tokens).type;
		++m_index;

		std::unique_ptr<Node> right = ParseMultiplication(tokens);

		auto node = std::make_unique<Node>();
		node->type = op;
		node->left = std::move(left);
		node->right = std::move(right);

		left = std::move(node);
	}

	return left;
}

std::unique_ptr<Node> Parser::ParseMultiplication(const std::vector<Token>& tokens)
{
	std::unique_ptr<Node> left = ParseUnary(tokens);

	while (!IsAtEnd(tokens) &&
	       (Peek(tokens).type == TokenType::MULTIPLICATION ||
	        Peek(tokens).type == TokenType::DIVISION))
	{
		TokenType op = Peek(tokens).type;
		++m_index;

		std::unique_ptr<Node> right = ParseUnary(tokens);

		auto node = std::make_unique<Node>();
		node->type = op;
		node->left = std::move(left);
		node->right = std::move(right);

		left = std::move(node);
	}

	return left;
}

std::unique_ptr<Node> Parser::ParseUnary(const std::vector<Token>& tokens)
{
	if (!IsAtEnd(tokens) && Peek(tokens).type == TokenType::MINUS)
	{
		++m_index;

		auto node = std::make_unique<Node>();
		node->type = TokenType::UNARY_MINUS;
		node->right = ParseUnary(tokens);

		return node;
	}

	if (!IsAtEnd(tokens) && Peek(tokens).type == TokenType::PLUS)
	{
		++m_index;
		return ParseUnary(tokens);
	}

	return ParsePower(tokens);
}

std::unique_ptr<Node> Parser::ParsePower(const std::vector<Token>& tokens)
{
	std::unique_ptr<Node> left = ParsePrimary(tokens);

	if (!IsAtEnd(tokens) && Peek(tokens).type == TokenType::POWER)
	{
		++m_index;

		auto node = std::make_unique<Node>();
		node->type = TokenType::POWER;
		node->left = std::move(left);
		node->right = ParseUnary(tokens);

		return node;
	}

	return left;
}

std::unique_ptr<Node> Parser::ParsePrimary(const std::vector<Token>& tokens)
{
	if (IsAtEnd(tokens) || Peek(tokens).type == TokenType::END_OF_LINE)
	{
		throw ExpressionError("Unexpected end of expression, expected a number, '(' or 'sqrt'");
	}

	const Token& cur_token = Peek(tokens);

	if (cur_token.type == TokenType::NUMBER)
	{
		auto node = std::make_unique<Node>();
		node->type = TokenType::NUMBER;

		try
		{
			node->value = std::stod(cur_token.value);
		}
		catch (const std::exception&)
		{
			throw ExpressionError("Invalid number '" + cur_token.value + "'");
		}

		++m_index;

		return node;
	}

	if (cur_token.type == TokenType::SQRT)
	{
		++m_index;

		if (IsAtEnd(tokens) || Peek(tokens).type != TokenType::LPAREN)
		{
			throw ExpressionError("Expected '(' after 'sqrt'");
		}
		++m_index;

		std::unique_ptr<Node> inner = ParseAdditive(tokens);

		if (IsAtEnd(tokens) || Peek(tokens).type != TokenType::RPAREN)
		{
			throw ExpressionError("Expected ')' to close 'sqrt('");
		}
		++m_index;

		auto node = std::make_unique<Node>();
		node->type = TokenType::SQRT;
		node->right = std::move(inner);

		return node;
	}

	if (cur_token.type == TokenType::LPAREN)
	{
		++m_index;

		std::unique_ptr<Node> inner = ParseAdditive(tokens);

		if (IsAtEnd(tokens) || Peek(tokens).type != TokenType::RPAREN)
		{
			throw ExpressionError("Expected ')' to close '('");
		}
		++m_index;

		return inner;
	}

	throw ExpressionError("Unexpected token '" + cur_token.value + "'");
}
