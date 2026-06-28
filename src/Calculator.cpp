#include "Calculator.h"
#include "RpnEvaluator.h"

#include <vector>
#include <cctype>

namespace 
{
	static const std::vector<char> ops{ '+', '-', '/', '*'};
    static const double epsilon = 1e-9;
}

Calculator::Calculator(QObject* parent) : QObject(parent) 
{

}

void Calculator::changeExpression(const std::string& expression) 
{
    m_expression = expression;
    emit expressionChanged(m_expression);
}

std::optional<double> Calculator::evaluate(const std::string& expression) 
{
    if (!validateExpression(expression)) 
    {
        emit evaluated(std::nullopt);
        return std::nullopt;
    }

    auto val = RpnEvaluator::evaluate(expression);
    if (val) 
    {
        const auto value = val.value();
        if (std::abs(value - std::round(value)) < epsilon) 
        {
            m_expression = std::to_string(static_cast<int>(value));
        }
        else 
        {
            m_expression = std::to_string(val.value());
        }
    }
    
    emit evaluated(val);
    return val;
}

std::optional<double> Calculator::evaluate() 
{
    auto val = evaluate(m_expression);
    return val;
}


bool Calculator::addInt(int number) 
{
	std::string expression = m_expression + std::to_string(number);
	if (validatePartial(expression))
	{
        m_expression = expression;
        emit expressionChanged(m_expression);
		return true;
	}

	return false;
}

bool Calculator::addOperator(char op)
{
	std::string expression = m_expression + op;
	if (validatePartial(expression))
	{
        m_expression = expression;
        emit expressionChanged(m_expression);
		return true;
	}

	return false;
}

bool Calculator::validateExpression(std::string_view expression) const
{
    if (expression.empty()) 
    {
        return false;
    }

    int open_parentheses = 0;
    bool expect_operand = true;
    bool has_dot_in_number = false;
    bool has_digits = false;

    for (char c : expression) 
    {
        if (std::isspace(c)) 
        {
            continue;
        }

        if (std::isdigit(c)) 
        {
            expect_operand = false;
            has_digits = true;
        }
        else if (c == '.') {
            if (has_dot_in_number) 
            {
                return false;
            }

            has_dot_in_number = true;
            expect_operand = true;
        }
        else if (c == '(') 
        {
            ++open_parentheses;
            expect_operand = true;
            has_dot_in_number = false;
        }
        else if (c == ')') {
            open_parentheses--;
            if (open_parentheses < 0) 
            {
                return false;
            }

            if (expect_operand) 
            {
                return false;
            }

            has_dot_in_number = false;
        }
        else if (c == '-' || c == '+') 
        {
            expect_operand = true;
            has_dot_in_number = false;
        }
        else if (c == '*' || c == '/' || c == '%' || c == '^') {
            if (expect_operand) 
            {
                return false;
            }

            expect_operand = true;
            has_dot_in_number = false;
        }
        else 
        {
            return false;
        }
    }

    if (open_parentheses != 0) 
    {
        return false;
    } 
    if (expect_operand) 
    {
        return false;
    }
    if (!has_digits) 
    {
        return false;
    } 

    return true;
}

bool Calculator::validatePartial(std::string_view expression) const
{
    if (expression.empty()) 
    {
        return true;
    }

    int open_parentheses = 0;
    bool expect_operand = true;
    bool has_dot_in_number = false;
    bool prev_was_operator = false;

    for (size_t i = 0; i < expression.size(); ++i)
    {
        char c = expression[i];

        if (std::isspace(c)) 
        {
            continue;
        }

        if (std::isdigit(c))
        {
            expect_operand = false;
            prev_was_operator = false;
            has_dot_in_number = false;
        }
        else if (c == '.')
        {
            if (has_dot_in_number) 
            {
                return false;
            }

            has_dot_in_number = true;
            prev_was_operator = false;
        }
        else if (c == '(')
        {
            ++open_parentheses;
            expect_operand = true;
            has_dot_in_number = false;
            prev_was_operator = false;
        }
        else if (c == ')')
        {
            if (--open_parentheses < 0) 
            {
                return false;
            }

            if (expect_operand) 
            {
                return false;
            }

            has_dot_in_number = false;
            prev_was_operator = false;
        }
        else if (c == '-' || c == '+')
        {
            if (prev_was_operator)
            {
                return false;
            }

            prev_was_operator = true;
            expect_operand = true;
            has_dot_in_number = false;
        }
        else if (c == '*' || c == '/' || c == '%' || c == '^')
        {
            if (expect_operand) 
            {
                return false;
            }

            prev_was_operator = true;
            expect_operand = true;
            has_dot_in_number = false;
        }
        else
        {
            return false;
        }

        if (std::isdigit(c)) 
        {
            expect_operand = false;
        }      
    }

    return true;
}

bool Calculator::addOpenParenthesis()
{
    std::string expression = m_expression + "(";
    if (validatePartial(expression))
    {
        m_expression = expression;
        emit expressionChanged(m_expression);
        return true;
    }

    return false;
}

bool Calculator::addCloseParenthesis()
{
    std::string expression = m_expression + ")";
    if (validatePartial(expression))
    {
        m_expression = expression;
        emit expressionChanged(m_expression);
        return true;
    }

    return false;
}

bool Calculator::addDot() 
{
    std::string expression = m_expression + ".";
    if (validatePartial(expression))
    {
        m_expression = expression;
        emit expressionChanged(m_expression);
        return true;
    }

    return false;
}
