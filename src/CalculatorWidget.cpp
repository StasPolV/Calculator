#include "CalculatorWidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QDebug>

namespace 
{
	enum CalculatorButtons 
	{
		BUTTON_0,
		BUTTON_1,
		BUTTON_2,
		BUTTON_3,
		BUTTON_4,
		BUTTON_5,
		BUTTON_6,
		BUTTON_7,
		BUTTON_8,
		BUTTON_9,
		BUTTON_RESULT,
		BUTTON_COMMA,
		BUTTON_ADDITION,
		BUTTON_SUBTRACTION,
		BUTTON_DIVISION,
		BUTTON_MULTIPLICATION,
		Count,
	};
}

CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent)
{
	setFocusPolicy(Qt::StrongFocus);
	m_buttons.resize(CalculatorButtons::Count, nullptr);

	for (size_t i = 0; i < m_buttons.size(); ++i) 
	{
		m_buttons[i] = new QPushButton(this);
	}

	for (QPushButton* button : m_buttons)
	{
		if (button) {
			button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		}
	}

	QPushButton*& button_0 = m_buttons[CalculatorButtons::BUTTON_0];
	QPushButton*& button_1 = m_buttons[CalculatorButtons::BUTTON_1];
	QPushButton*& button_2 = m_buttons[CalculatorButtons::BUTTON_2];
	QPushButton*& button_3 = m_buttons[CalculatorButtons::BUTTON_3];
	QPushButton*& button_4 = m_buttons[CalculatorButtons::BUTTON_4];
	QPushButton*& button_5 = m_buttons[CalculatorButtons::BUTTON_5];
	QPushButton*& button_6 = m_buttons[CalculatorButtons::BUTTON_6];
	QPushButton*& button_7 = m_buttons[CalculatorButtons::BUTTON_7];
	QPushButton*& button_8 = m_buttons[CalculatorButtons::BUTTON_8];
	QPushButton*& button_9 = m_buttons[CalculatorButtons::BUTTON_9];
	QPushButton*& button_result = m_buttons[CalculatorButtons::BUTTON_RESULT];
	QPushButton*& button_comma = m_buttons[CalculatorButtons::BUTTON_COMMA];
	QPushButton*& button_addition = m_buttons[CalculatorButtons::BUTTON_ADDITION];
	QPushButton*& button_subtraction = m_buttons[CalculatorButtons::BUTTON_SUBTRACTION];
	QPushButton*& button_division = m_buttons[CalculatorButtons::BUTTON_DIVISION];
	QPushButton*& button_multiplication = m_buttons[CalculatorButtons::BUTTON_MULTIPLICATION];

	button_0->setText("0");
	button_1->setText("1");
	button_2->setText("2");
	button_3->setText("3");
	button_4->setText("4");
	button_5->setText("5");
	button_6->setText("6");
	button_7->setText("7");
	button_8->setText("8");
	button_9->setText("9");
	button_result->setText("=");
	button_comma->setText(",");
	button_addition->setText("+");
	button_subtraction->setText("-");
	button_division->setText("÷");
	button_multiplication->setText("*");

	QGridLayout* grid_layout = new QGridLayout;
	grid_layout->setSpacing(0);
	grid_layout->setContentsMargins(0, 0, 0, 0);
	grid_layout->addWidget(button_7, 0, 0);
	grid_layout->addWidget(button_8, 0, 1);
	grid_layout->addWidget(button_9, 0, 2);
	grid_layout->addWidget(button_4, 1, 0);
	grid_layout->addWidget(button_5, 1, 1);
	grid_layout->addWidget(button_6, 1, 2);
	grid_layout->addWidget(button_1, 2, 0);
	grid_layout->addWidget(button_2, 2, 1);
	grid_layout->addWidget(button_3, 2, 2);
	grid_layout->addWidget(button_0, 3, 0);
	grid_layout->addWidget(button_comma, 3, 1);
	grid_layout->addWidget(button_result, 3, 2);

	QVBoxLayout* vbox_layout = new QVBoxLayout;
	vbox_layout->setSpacing(0);
	vbox_layout->setContentsMargins(0, 0, 0, 0);
	vbox_layout->addWidget(button_division);
	vbox_layout->addWidget(button_multiplication);
	vbox_layout->addWidget(button_subtraction);
	vbox_layout->addWidget(button_addition);

	QFont label_font;
	label_font.setFamily("Arial");
	label_font.setPointSize(24);
	label_font.setBold(true);

	m_label = new QLabel(this);
	m_label->setFont(label_font);
	m_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	QHBoxLayout* hbox_layout = new QHBoxLayout;
	hbox_layout->setSpacing(0);
	hbox_layout->setContentsMargins(0, 0, 0, 0);
	hbox_layout->addLayout(grid_layout);
	hbox_layout->addLayout(vbox_layout);

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->addWidget(m_label, 1);
	main_layout->addLayout(hbox_layout, 5);

	resize(400, 300);

}

void CalculatorWidget::keyPressEvent(QKeyEvent* event) 
{

	switch (auto key = event->key(); key)
	{
	case Qt::Key_0:
		labelAddition("0");
		break;
	case Qt::Key_1:
		labelAddition("1");
		break;
	case Qt::Key_2:
		labelAddition("2");
		break;
	case Qt::Key_3:
		labelAddition("3");
		break;
	case Qt::Key_4:
		labelAddition("4");
		break;
	case Qt::Key_5:
		labelAddition("5");
		break;
	case Qt::Key_6:
		labelAddition("6");
		break;
	case Qt::Key_7:
		labelAddition("7");
		break;
	case Qt::Key_8:
		labelAddition("8");
		break;
	case Qt::Key_9:
		labelAddition("9");
		break;
	case Qt::Key_Plus:
		labelAddition("+");
		break;
	case Qt::Key_Minus:
		labelAddition("-");
		break;
	case Qt::Key_Asterisk:
		labelAddition("*");
		break;
	case Qt::Key_Slash:
		labelAddition("÷");
		break;
	default:
		QWidget::keyPressEvent(event);
		break;
	}
}

void CalculatorWidget::labelAddition(const QString& text)
{
	m_label->setText(m_label->text() + text);
}
