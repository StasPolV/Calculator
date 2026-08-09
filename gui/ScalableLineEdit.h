#pragma once

#include <QLineEdit>

class QResizeEvent;

class ScalableLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	explicit ScalableLineEdit(QWidget* parent = nullptr);

	void SetFontRatio(double ratio);

protected:
	void resizeEvent(QResizeEvent* event) override;
	void changeEvent(QEvent* event) override;

private:
	void UpdateFont();

	double m_font_ratio = 0.5;
};
