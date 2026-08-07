#pragma once

#include <QWidget>
#include <QString>

class KeypadWidget : public QWidget
{
	Q_OBJECT

signals:
	void DigitPressed(QString digit);
	void OperatorPressed(QString op);
	void EqualsPressed();
	void ClearRequested();

	void FunctionRequested(QString format_template);

public:
	explicit KeypadWidget(QWidget* parent = nullptr);
};
