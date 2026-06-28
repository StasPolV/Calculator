#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QKeyEvent>
#include <QString>

#include "Calculator.h"

#include <vector>
#include <memory>

class CalculatorWidget : public QWidget 
{
	Q_OBJECT

public:
	CalculatorWidget(QWidget* parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	// void labelAddition(const QString& text);

	std::unique_ptr<Calculator> m_calc;
	std::vector<QPushButton*> m_buttons;
	QLabel* m_label;
};
