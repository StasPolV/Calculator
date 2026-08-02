#include "Tokenizer.h"

void Tokenizer::Tokenize(const std::string& expression) 
{
    m_tokens.clear();

    size_t start_digit_index = 0;
    bool is_digit = false;

    for (size_t i = 0; i < expression.size(); ++i)
    {
        char symbol = expression[i];

        if ((symbol >= '0' && symbol <= '9') || symbol == '.')
        {
            if (!is_digit) 
            {
                start_digit_index = i;
            }
            is_digit = true;
        }
        else
        {
            if (is_digit) 
            {
                m_tokens.emplace_back(TokenType::NUMBER, expression.substr(start_digit_index, i - start_digit_index));
                is_digit = false;
            }

            switch (symbol)
            {
            case '(':
                m_tokens.emplace_back(TokenType::LPAREN, std::string(1, symbol));
                break;
            case ')':
                m_tokens.emplace_back(TokenType::RPAREN, std::string(1, symbol));
                break;
            case '+':
                m_tokens.emplace_back(TokenType::PLUS, std::string(1, symbol));
                break;
            case '-':
                m_tokens.emplace_back(TokenType::MINUS, std::string(1, symbol));
                break;
            case '*':
                m_tokens.emplace_back(TokenType::MULTIPLICATION, std::string(1, symbol));
                break;
            case '/':
                m_tokens.emplace_back(TokenType::DIVISION, std::string(1, symbol));
                break;
            case ' ':
                break;
            }
        }
    }

    if (is_digit) 
    {
        m_tokens.emplace_back(TokenType::NUMBER, expression.substr(start_digit_index));
    }

    m_tokens.emplace_back(TokenType::END_OF_LINE, "Empty");
}

const std::vector<Token>& Tokenizer::GetTokens() const 
{
    return m_tokens;
}
