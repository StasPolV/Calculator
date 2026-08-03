#pragma once

#include <string>

class CalculatorModel 
{
public:
	void SetExpression(const std::string& expression);
	const std::string& GetExpression() const { return m_expression; }
	double Evaluate();

private:
	std::string m_expression;
};
