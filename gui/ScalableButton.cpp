#include "ScalableButton.h"

#include <QFont>
#include <QResizeEvent>

#include <algorithm>

ScalableButton::ScalableButton(QWidget* parent) : QPushButton(parent)
{
}

ScalableButton::ScalableButton(QString text, QWidget* parent) : QPushButton(text, parent)
{
}

void ScalableButton::SetFontRatio(double ratio)
{
	m_font_ratio = std::clamp(ratio, 0.05, 1.0);
	UpdateFont();
}

void ScalableButton::resizeEvent(QResizeEvent* event)
{
	QPushButton::resizeEvent(event);
	UpdateFont();
}

void ScalableButton::UpdateFont()
{
	const int pixel_size = std::max(1, static_cast<int>(std::min(width(), height()) * m_font_ratio));

	QFont current_font = font();
	if (current_font.pixelSize() == pixel_size)
	{
		return;
	}

	current_font.setPixelSize(pixel_size);
	setFont(current_font);
}
