#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum TokenType : std::uint8_t
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
	void FlushDigitToken(const std::string& expression, size_t start, size_t end);
	void FlushAlphaToken(const std::string& expression, size_t start, size_t end);
	void EmplaceSymbolToken(char symbol);

	std::vector<Token> m_tokens;
};
