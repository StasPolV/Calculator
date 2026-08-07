#pragma once

#include <QWidget>
#include <QString>

#include <string>

class QLineEdit;
class QLabel;

class DisplayWidget : public QWidget
{
	Q_OBJECT

signals:
	void EvaluateRequested(const std::string& expression);

public slots:
	void ShowResult(double result);
	void ShowError(QString error);

public:
	explicit DisplayWidget(QWidget* parent = nullptr);

	void InsertText(const QString& text);
	void SetText(const QString& text);
	QString Text() const;
	void Clear();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void UpdateStyle();
	void ResetErrorStyle();

	QLineEdit* m_line_edit;
	QLabel* m_label;
};
