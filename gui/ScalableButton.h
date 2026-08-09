#pragma once

#include <QPushButton>
#include <QString>

class QResizeEvent;

class ScalableButton : public QPushButton
{
	Q_OBJECT

public:
	explicit ScalableButton(QWidget* parent = nullptr);
	explicit ScalableButton(QString text, QWidget* parent = nullptr);

	void SetFontRatio(double ratio);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void UpdateFont();

	double m_font_ratio = 0.4;
};
