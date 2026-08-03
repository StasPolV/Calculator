#pragma once

#include "CalculatorWidget.h"
#include "CalculatorModel.h"

#include <QObject>

class CalculatorController : public QObject
{
	Q_OBJECT
public:
	CalculatorController(CalculatorModel& model, CalculatorWidget& widget, QObject* parent = nullptr);

private:
	CalculatorModel& m_model;
	CalculatorWidget& m_widget;
};
