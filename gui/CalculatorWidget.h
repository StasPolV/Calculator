#pragma once

#include <QWidget>
#include <QLineEdit>

class CalculatorWidget : public QWidget
{
	Q_OBJECT
public:
	CalculatorWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QLineEdit* m_line_edit;
};
