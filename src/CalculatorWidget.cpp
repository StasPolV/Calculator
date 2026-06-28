#include "CalculatorWidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QDebug>

#include <map>

namespace 
{
	enum class CalculatorButtons 
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
	m_buttons.resize(static_cast<size_t>(CalculatorButtons::Count), nullptr);


	struct ButtonDef 
	{
		CalculatorButtons id;
		QString label;
	};

	static const std::array<ButtonDef, static_cast<size_t>(CalculatorButtons::Count)> defs = { {
		{CalculatorButtons::BUTTON_0, "0"}, {CalculatorButtons::BUTTON_1, "1"}, {CalculatorButtons::BUTTON_2, "2"}, {CalculatorButtons::BUTTON_3, "3"},
		{CalculatorButtons::BUTTON_4, "4"}, {CalculatorButtons::BUTTON_5, "5"}, {CalculatorButtons::BUTTON_6, "6"}, {CalculatorButtons::BUTTON_7, "7"},
		{CalculatorButtons::BUTTON_8, "8"}, {CalculatorButtons::BUTTON_9, "9"}, {CalculatorButtons::BUTTON_RESULT, "="}, {CalculatorButtons::BUTTON_COMMA, ","},
		{CalculatorButtons::BUTTON_ADDITION, "+"}, {CalculatorButtons::BUTTON_SUBTRACTION, "-"}, {CalculatorButtons::BUTTON_DIVISION, "÷"}, {CalculatorButtons::BUTTON_MULTIPLICATION, "*"}
	} };

	for (auto& [id, label] : defs) 
	{
		auto& button = m_buttons[static_cast<size_t>(id)];
		button = new QPushButton(label, this);
		button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	}

	QGridLayout* grid_layout = new QGridLayout;
	grid_layout->setSpacing(0);
	grid_layout->setContentsMargins(0, 0, 0, 0);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_7)], 0, 0);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_8)], 0, 1);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_9)], 0, 2);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_4)], 1, 0);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_5)], 1, 1);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_6)], 1, 2);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_1)], 2, 0);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_2)], 2, 1);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_3)], 2, 2);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_0)], 3, 0);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_COMMA)], 3, 1);
	grid_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_RESULT)], 3, 2);

	QVBoxLayout* vbox_layout = new QVBoxLayout;
	vbox_layout->setSpacing(0);
	vbox_layout->setContentsMargins(0, 0, 0, 0);
	vbox_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_DIVISION)]);
	vbox_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_MULTIPLICATION)]);
	vbox_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_SUBTRACTION)]);
	vbox_layout->addWidget(m_buttons[static_cast<size_t>(CalculatorButtons::BUTTON_ADDITION)]);

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

	static const  std::map<int, QString> key_map = {
		{Qt::Key_0, "0"}, {Qt::Key_1, "1"}, {Qt::Key_2, "2"}, {Qt::Key_3, "3"}, {Qt::Key_4, "4"}, 
		{Qt::Key_5, "5"}, {Qt::Key_6, "6"}, {Qt::Key_7, "7"}, {Qt::Key_8, "8"}, 
		{Qt::Key_9, "9"}, {Qt::Key_Plus, "+"}, {Qt::Key_Minus, "-"}, {Qt::Key_Asterisk, "*"}, {Qt::Key_Slash, "÷"},
	};

	if (auto it = key_map.find(event->key()); it != key_map.end()) 
	{
		labelAddition(it->second);
	}
	else 
	{
		QWidget::keyPressEvent(event);
	}
}

void CalculatorWidget::labelAddition(const QString& text)
{
	m_label->setText(m_label->text() + text);
}
