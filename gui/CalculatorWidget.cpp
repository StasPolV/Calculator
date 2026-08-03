#include "CalculatorWidget.h"

#include <QLayout>
#include <QPushButton>
#include <QString>

CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent)
{
	m_line_edit = new QLineEdit(this);
	m_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QGridLayout* main_layout = new QGridLayout(this);


	main_layout->addWidget(m_line_edit, 0, 0, 1, 3);

	/*for (size_t i = 9; i >= 0; --i) 
	{
		QPushButton* button = new QPushButton(QString::fromStdString(std::to_string(i)), this);


	}*/

	QPushButton* button_7 = new QPushButton("7", this);
	button_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton* button_8 = new QPushButton("8", this);
	button_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton* button_9 = new QPushButton("9", this);
	button_9->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QPushButton* button_4 = new QPushButton("4", this);
	button_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton* button_5 = new QPushButton("5", this);
	button_5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton* button_6 = new QPushButton("6", this);
	button_6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QPushButton* button_1 = new QPushButton("1", this);
	button_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton* button_2 = new QPushButton("2", this);
	button_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPushButton* button_3 = new QPushButton("3", this);
	button_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	main_layout->addWidget(button_7, 1, 0);
	main_layout->addWidget(button_8, 1, 1);
	main_layout->addWidget(button_9, 1, 2);

	main_layout->addWidget(button_4, 2, 0);
	main_layout->addWidget(button_5, 2, 1);
	main_layout->addWidget(button_6, 2, 2);

	main_layout->addWidget(button_1, 3, 0);
	main_layout->addWidget(button_2, 3, 1);
	main_layout->addWidget(button_3, 3, 2);

	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

	main_layout->setRowStretch(0, 1);
	main_layout->setRowStretch(1, 2);
	main_layout->setRowStretch(2, 2);
	main_layout->setRowStretch(3, 2);
}
