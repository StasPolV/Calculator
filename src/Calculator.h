#pragma once

#include <QObject>

#include <string>
#include <stack>
#include <string_view>
#include <optional>

class Calculator : public QObject 
{
	Q_OBJECT

signals:
	void expressionChanged(const std::string& expression);
	void evaluated(std::optional<double> val);

public:
	Calculator(QObject* parent = nullptr);

	// Сompute from string representation
	std::optional<double> evaluate(const std::string& expression);

	// Compute after after methods with "add"
	std::optional<double> evaluate();

	bool addInt(int number);
	bool addOperator(char op);
	bool addOpenParenthesis();
	bool addCloseParenthesis();
	bool addDot();

private:
	bool validateExpression(std::string_view expression) const;
	bool validatePartial(std::string_view expression) const;

	std::stack<double> m_stack;
	std::string m_expression;
};