#pragma once

#include "Evaluator.h"
#include "Parser.h"
#include "Tokenizer.h"

#include <string>

class ExpressionCalculator
{
public:
	double Evaluate(const std::string& expression)
	{
		Tokenizer tokenizer;
		tokenizer.Tokenize(expression);

		Parser parser;
		parser.Parse(tokenizer.GetTokens());

		Evaluator evaluator;
		evaluator.Evaluate(parser.GetAstRoot());

		return evaluator.GetResult();
	}
};
