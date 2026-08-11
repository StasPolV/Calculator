#include "CalculatorModel.h"

#include <gtest/gtest.h>

TEST(CalculatorModelTest, SetAndGetExpressionRoundTrip)
{
	CalculatorModel model;
	model.SetExpression("2 + 2");

	EXPECT_EQ(model.GetExpression(), "2 + 2");
}

TEST(CalculatorModelTest, EvaluateEmitsResultForValidExpression)
{
	CalculatorModel model;
	model.SetExpression("3 + 4 * 2");

	bool got_result = false;
	double result = 0.0;
	QObject::connect(&model, &CalculatorModel::Evaluated, &model,
	                 [&](double value)
	                 {
		                 got_result = true;
		                 result = value;
	                 });

	bool got_error = false;
	QObject::connect(&model, &CalculatorModel::EvaluatedError, &model,
	                 [&](const std::string&) { got_error = true; });

	model.Evaluate();

	EXPECT_TRUE(got_result);
	EXPECT_FALSE(got_error);
	EXPECT_DOUBLE_EQ(result, 11.0);
}

TEST(CalculatorModelTest, EvaluateEmitsErrorOnDivisionByZero)
{
	CalculatorModel model;
	model.SetExpression("1 / 0");

	bool got_error = false;
	std::string message;
	QObject::connect(&model, &CalculatorModel::EvaluatedError, &model,
	                 [&](const std::string& msg)
	                 {
		                 got_error = true;
		                 message = msg;
	                 });

	bool got_result = false;
	QObject::connect(&model, &CalculatorModel::Evaluated, &model,
	                 [&](double) { got_result = true; });

	model.Evaluate();

	EXPECT_TRUE(got_error);
	EXPECT_FALSE(got_result);
	EXPECT_EQ(message, "Zero Division Error");
}

TEST(CalculatorModelTest, EvaluateEmitsErrorOnUnparsableExpression)
{
	CalculatorModel model;
	model.SetExpression("2 + ");

	bool got_error = false;
	QObject::connect(&model, &CalculatorModel::EvaluatedError, &model,
	                 [&](const std::string&) { got_error = true; });

	model.Evaluate();

	EXPECT_TRUE(got_error);
}

TEST(CalculatorModelTest, EvaluateEmitsErrorOnUnknownSymbol)
{
	CalculatorModel model;
	model.SetExpression("3 & 4");

	bool got_error = false;
	QObject::connect(&model, &CalculatorModel::EvaluatedError, &model,
	                 [&](const std::string&) { got_error = true; });

	model.Evaluate();

	EXPECT_TRUE(got_error);
}
