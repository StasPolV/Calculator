#include "CalculatorModel.h"

#include "ExpressionCalculator.h"
#include "ExpressionError.h"

void CalculatorModel::SetExpression(const std::string& expression)
{
	m_expression = expression;
}

void CalculatorModel::Evaluate()
{
	try
	{
		ExpressionCalculator expr_calc;
		double result = expr_calc.Evaluate(m_expression);
		emit Evaluated(result);
	}
	catch (const ExpressionError& e)
	{
		emit EvaluatedError(e.what());
	}
}
