#pragma once

#include <QWidget>
#include <QString>

#include <string>

class ScalableLineEdit;
class QLabel;

class DisplayWidget : public QWidget
{
	Q_OBJECT

signals:
	void EvaluateRequested(const std::string& expression);

public slots:
	void ShowResult(double result);
	void ShowError(QString error);
	void SetPrecision(int precision);

public:
	explicit DisplayWidget(QWidget* parent = nullptr);

	void InsertText(const QString& text);
	void SetText(const QString& text);
	QString Text() const;
	void Clear();

private:
	void UpdateStyle();
	void ResetErrorStyle();

	ScalableLineEdit* m_line_edit;
	QLabel* m_label;
	int m_precision = 2;
};
