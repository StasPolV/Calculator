#include "CalculatorController.h"

CalculatorController::CalculatorController(CalculatorModel& model, CalculatorWidget& widget, QObject* parent)
	: m_model(model), m_widget(widget), QObject(parent) 
{
}
