#include "RpnEvaluator.h"
#include <stack>
#include <cctype>
#include <cmath>

std::optional<double> RpnEvaluator::evaluate(const std::string& expression)
{
    std::vector<std::string> rpn = convertToRpn(expression);

    return calculateRpn(rpn);
}

int RpnEvaluator::get_precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }
    if (op == '^')
    {
        return 3;
    }

    return 0;
}

std::vector<std::string> RpnEvaluator::convertToRpn(const std::string& expression)
{
    std::vector<std::string> rpn;
    std::stack<char> operators;
    bool expect_unary = true;

    for (size_t i = 0; i < expression.length(); ++i)
    {
        char c = expression[i];
        if (std::isspace(c))
        {
            continue;
        }

        if (std::isdigit(c) || c == '.')
        {
            std::string num;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.'))
            {
                num += expression[i++];
            }

            --i;
            rpn.push_back(num);
            expect_unary = false;
        }
        else if ((c == '-' || c == '+') && expect_unary)
        {
            if (c == '-')
            {
                std::string num = "-";
                ++i;
                while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.'))
                {
                    num += expression[i++];
                }

                --i;
                rpn.push_back(num);
            }
            expect_unary = false;
        }
        else if (c == '(')
        {
            operators.push(c);
            expect_unary = true;
        }
        else if (c == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                rpn.push_back(std::string(1, operators.top()));
                operators.pop();
            }

            if (!operators.empty()) operators.pop();
            expect_unary = false;
        }
        else
        {
            while (!operators.empty() && get_precedence(operators.top()) >= get_precedence(c))
            {
                if (c == '^' && operators.top() == '^')
                {
                    break;
                }

                rpn.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(c);
            expect_unary = true;
        }
    }

    while (!operators.empty())
    {
        rpn.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    return rpn;
}

std::optional<double> RpnEvaluator::calculateRpn(const std::vector<std::string>& rpn)
{
    std::stack<double> values;

    for (const auto& token : rpn)
    {
        if (token.length() > 1 || std::isdigit(token[0]))
        {
            try
            {
                values.push(std::stod(token));
            }
            catch (...)
            {
                return std::nullopt;
            }
        }
        else
        {
            if (values.size() < 2)
            {
                return std::nullopt;
            }

            double right = values.top(); values.pop();
            double left = values.top(); values.pop();
            char op = token[0];

            if (op == '+')
            {
                values.push(left + right);
            }
            else if (op == '-')
            {
                values.push(left - right);
            }
            else if (op == '*')
            {
                values.push(left * right);
            }
            else if (op == '/')
            {
                if (right == 0.0)
                {
                    return std::nullopt;
                }

                values.push(left / right);
            }
            else if (op == '^')
            {
                values.push(std::pow(left, right));
            }
            else if (op == '%')
            {
                if (right == 0.0)
                {
                    return std::nullopt;
                }

                values.push(std::fmod(left, right));
            }
        }
    }

    if (values.size() == 1)
    {
        return values.top();
    }

    return std::nullopt;
}