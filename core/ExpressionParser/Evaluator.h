#pragma once

#include "Parser.h"

class Evaluator
{
public:
	void Evaluate(std::unique_ptr<Node> ast_root);
	double GetResult() const;

private:
	double EvaluateHelper(Node* cur_node);

	double m_result = 0;
};
