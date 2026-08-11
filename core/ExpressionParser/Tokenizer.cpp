#include "Tokenizer.h"

#include "ExpressionError.h"

namespace
{
	bool isDigitOrDot(char symbol)
	{
		return (symbol >= '0' && symbol <= '9') || symbol == '.';
	}

	bool isLowerAlpha(char symbol)
	{
		return symbol >= 'a' && symbol <= 'z';
	}
}  // namespace

void Tokenizer::FlushDigitToken(const std::string& expression, size_t start, size_t end)
{
	m_tokens.emplace_back(TokenType::NUMBER, expression.substr(start, end - start));
}

void Tokenizer::FlushAlphaToken(const std::string& expression, size_t start, size_t end)
{
	const std::string identifier = expression.substr(start, end - start);
	if (identifier == "sqrt")
	{
		m_tokens.emplace_back(TokenType::SQRT, identifier);
	}
	else
	{
		throw ExpressionError("Unknown identifier '" + identifier + "'");
	}
}

void Tokenizer::EmplaceSymbolToken(char symbol)
{
	switch (symbol)
	{
	case '(': m_tokens.emplace_back(TokenType::LPAREN, std::string(1, symbol)); break;
	case ')': m_tokens.emplace_back(TokenType::RPAREN, std::string(1, symbol)); break;
	case '+': m_tokens.emplace_back(TokenType::PLUS, std::string(1, symbol)); break;
	case '-': m_tokens.emplace_back(TokenType::MINUS, std::string(1, symbol)); break;
	case '*': m_tokens.emplace_back(TokenType::MULTIPLICATION, std::string(1, symbol)); break;
	case '/': m_tokens.emplace_back(TokenType::DIVISION, std::string(1, symbol)); break;
	case '^': m_tokens.emplace_back(TokenType::POWER, std::string(1, symbol)); break;
	case ' ': break;
	default: throw ExpressionError("Unknown symbol '" + std::string(1, symbol) + "'");
	}
}

void Tokenizer::Tokenize(const std::string& expression)
{
	m_tokens.clear();

	size_t start_digit_index = 0;
	bool is_digit = false;

	size_t start_alpha_index = 0;
	bool is_alpha = false;

	for (size_t i = 0; i < expression.size(); ++i)
	{
		const char symbol = expression[i];

		if (isDigitOrDot(symbol))
		{
			if (!is_digit)
			{
				start_digit_index = i;
			}
			is_digit = true;
			continue;
		}

		if (isLowerAlpha(symbol))
		{
			if (!is_alpha)
			{
				start_alpha_index = i;
			}
			is_alpha = true;
			continue;
		}

		if (is_digit)
		{
			FlushDigitToken(expression, start_digit_index, i);
			is_digit = false;
		}

		if (is_alpha)
		{
			FlushAlphaToken(expression, start_alpha_index, i);
			is_alpha = false;
		}

		EmplaceSymbolToken(symbol);
	}

	if (is_digit)
	{
		FlushDigitToken(expression, start_digit_index, expression.size());
	}

	if (is_alpha)
	{
		FlushAlphaToken(expression, start_alpha_index, expression.size());
	}

	m_tokens.emplace_back(TokenType::END_OF_LINE, "Empty");
}

const std::vector<Token>& Tokenizer::GetTokens() const
{
	return m_tokens;
}
