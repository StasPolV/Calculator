#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QKeyEvent>
#include <QString>

#include <vector>

class CalculatorWidget : public QWidget 
{
	Q_OBJECT

public:
	CalculatorWidget(QWidget* parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	void labelAddition(const QString& text);

	std::vector<QPushButton*> m_buttons;
	QLabel* m_label;
};
