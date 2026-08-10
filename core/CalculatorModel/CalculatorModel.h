#pragma once

#include <QObject>
#include <QString>

#include <string>

class CalculatorModel : public QObject
{
	Q_OBJECT

signals:
	void Evaluated(double result);
	void EvaluatedError(const std::string& message);

public slots:
	void Evaluate();

public:
	void SetExpression(const std::string& expression);
	const std::string& GetExpression() const { return m_expression; }
	CalculatorModel(QObject* parent = nullptr) : QObject(parent) {}

private:
	std::string m_expression;
};
