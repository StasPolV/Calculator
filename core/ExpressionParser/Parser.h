#pragma once

#include "Tokenizer.h"

#include <memory>

struct Node
{
	double value = 0;
	TokenType type;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
};

class Parser
{
public:
	void Parse(const std::vector<Token>& tokens);
	std::unique_ptr<Node> GetAstRoot();

private:
	std::unique_ptr<Node> ParseAdditive(const std::vector<Token>& tokens);
	std::unique_ptr<Node> ParseMultiplication(const std::vector<Token>& tokens);
	std::unique_ptr<Node> ParseUnary(const std::vector<Token>& tokens);
	std::unique_ptr<Node> ParsePower(const std::vector<Token>& tokens);
	std::unique_ptr<Node> ParsePrimary(const std::vector<Token>& tokens);

	bool IsAtEnd(const std::vector<Token>& tokens) const;
	const Token& Peek(const std::vector<Token>& tokens) const;

	std::unique_ptr<Node> m_ast_root;
	size_t m_index = 0;
};
