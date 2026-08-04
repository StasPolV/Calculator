#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QString>

class CalculatorWidget : public QWidget
{
	Q_OBJECT

signals:
	void EvaluateClicked(const std::string& expression);

public slots:
	void ClickDigit(QString digit);
	void ClickOp(QString op);
	void ShowResult(double result);

public:
	CalculatorWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QLineEdit* m_line_edit;
};
