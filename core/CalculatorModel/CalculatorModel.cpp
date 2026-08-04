#include "CalculatorModel.h"

#include "ExpressionCalculator.h"

void CalculatorModel::SetExpression(const std::string& expression)
{
	m_expression = expression;
}

double CalculatorModel::Evaluate()
{
	ExpressionCalculator expr_calc;
	return expr_calc.Evaluate(m_expression);
	// TODO: add errors handling
}
