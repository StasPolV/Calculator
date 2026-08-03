#pragma once

#include "Tokenizer.h"
#include "Parser.h"
#include "Evaluator.h"

#include <string>

class ExpressionCalculator 
{
public:
    double evaluate(const std::string& expression) 
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
