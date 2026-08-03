#pragma once

#include <QWidget>
#include <QLineEdit>

class CalculatorWidget : public QWidget
{
	Q_OBJECT
public:
	CalculatorWidget(QWidget* parent = nullptr);

private:
	QLineEdit* m_line_edit;
};
