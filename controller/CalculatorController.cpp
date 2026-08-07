#include "CalculatorController.h"

CalculatorController::CalculatorController(CalculatorModel& model, CalculatorWidget& widget, QObject* parent)
	: QObject(parent), m_model(model), m_widget(widget)
{
	connect(&m_widget, &CalculatorWidget::EvaluateClicked, &m_model, &CalculatorModel::SetExpression);
	connect(&m_widget, &CalculatorWidget::EvaluateClicked, &m_model, &CalculatorModel::Evaluate);
	// Don't swap the two lines above.
	// TODO: create one method Evaluate with a QString parameter

	connect(&m_model, &CalculatorModel::Evaluated, &m_widget, &CalculatorWidget::ShowResult);
	connect(&m_model, &CalculatorModel::EvaluatedError, 
		&m_widget, [this](const std::string& message) { m_widget.ShowError(QString::fromStdString(message)); });
}
