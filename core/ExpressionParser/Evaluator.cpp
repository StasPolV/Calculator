#include "Evaluator.h"

#include "ExpressionError.h"

#include <cmath>

double Evaluator::GetResult() const
{
	return m_result;
}

void Evaluator::Evaluate(std::unique_ptr<Node> ast_root)
{
	m_result = EvaluateHelper(ast_root.get());
}

double Evaluator::EvaluateHelper(Node* cur_node)
{
	if (cur_node == nullptr)
	{
		return 0;
	}
	if (cur_node->type == TokenType::NUMBER)
	{
		return cur_node->value;
	}

	const double left = EvaluateHelper(cur_node->left.get());
	const double right = EvaluateHelper(cur_node->right.get());

	double sum = 0;

	switch (cur_node->type)
	{
	case TokenType::MULTIPLICATION: sum = left * right; break;
	case TokenType::DIVISION:
		if (right == 0)
		{
			throw ExpressionError("Zero Division Error");
		}
		sum = left / right;
		break;
	case TokenType::MINUS: sum = left - right; break;
	case TokenType::PLUS: sum = left + right; break;
	case TokenType::UNARY_MINUS: sum = -right; break;
	case TokenType::POWER: sum = std::pow(left, right); break;
	case TokenType::SQRT: sum = std::sqrt(right); break;
	}

	return sum;
}
