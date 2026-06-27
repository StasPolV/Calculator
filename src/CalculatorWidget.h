#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>

#include <vector>

class CalculatorWidget : public QWidget 
{
	Q_OBJECT

public:
	CalculatorWidget(QWidget* parent = nullptr);

private:
	std::vector<QPushButton*> m_buttons;
	QLabel* m_label;
};
