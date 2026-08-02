#include "Parser.h"

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

	if (!IsAtEnd(tokens))
	{
		// TODO: add error handling
	}
}

std::unique_ptr<Node> Parser::ParseAdditive(const std::vector<Token>& tokens)
{
	std::unique_ptr<Node> left = ParseMultiplication(tokens);

	while (!IsAtEnd(tokens) && (Peek(tokens).type == TokenType::PLUS || Peek(tokens).type == TokenType::MINUS))
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
	std::unique_ptr<Node> left = ParsePrimary(tokens);

	while (!IsAtEnd(tokens) && (Peek(tokens).type == TokenType::MULTIPLICATION || Peek(tokens).type == TokenType::DIVISION))
	{
		TokenType op = Peek(tokens).type;
		++m_index;

		std::unique_ptr<Node> right = ParsePrimary(tokens);

		auto node = std::make_unique<Node>();
		node->type = op;
		node->left = std::move(left);
		node->right = std::move(right);

		left = std::move(node);
	}

	return left;
}

std::unique_ptr<Node> Parser::ParsePrimary(const std::vector<Token>& tokens)
{
	if (IsAtEnd(tokens))
	{
		// TODO: add error handling
	}

	const Token& cur_token = Peek(tokens);

	if (cur_token.type == TokenType::NUMBER)
	{
		auto node = std::make_unique<Node>();
		node->type = TokenType::NUMBER;
		node->value = std::stod(cur_token.value);

		++m_index;

		return node;
	}

	if (cur_token.type == TokenType::LPAREN)
	{
		++m_index;

		std::unique_ptr<Node> inner = ParseAdditive(tokens);

		if (IsAtEnd(tokens) || Peek(tokens).type != TokenType::RPAREN)
		{
			// TODO: add error handling
		}
		++m_index;

		return inner;
	}

	// TODO: add error handling
	return nullptr;
}
