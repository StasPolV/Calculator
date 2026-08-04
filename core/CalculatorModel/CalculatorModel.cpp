#include "CalculatorModel.h"

#include "ExpressionCalculator.h"

void CalculatorModel::SetExpression(const std::string& expression)
{
	m_expression = expression;
}

void CalculatorModel::Evaluate()
{
	ExpressionCalculator expr_calc;
	double result = expr_calc.Evaluate(m_expression);
	emit Evaluated(result);
	// TODO: add errors handling
}
