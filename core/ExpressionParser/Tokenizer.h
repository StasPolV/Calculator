#pragma once

#include <string>
#include <vector>

enum TokenType
{
	NUMBER,
	PLUS,
	MINUS,
	DIVISION,
	MULTIPLICATION,
	LPAREN,
	RPAREN,
	END_OF_LINE,
	UNARY_MINUS,
	POWER,
	SQRT,
};

struct Token
{
	TokenType type;
	std::string value;
};

class Tokenizer
{
public:
	void Tokenize(const std::string& expression);
	const std::vector<Token>& GetTokens() const;

private:
	std::vector<Token> m_tokens;
};
