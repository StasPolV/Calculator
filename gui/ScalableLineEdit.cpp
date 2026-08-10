#include "ScalableLineEdit.h"

#include <QFont>
#include <QResizeEvent>

#include <algorithm>

ScalableLineEdit::ScalableLineEdit(QWidget* parent) : QLineEdit(parent) {}

void ScalableLineEdit::SetFontRatio(double ratio)
{
	m_font_ratio = std::clamp(ratio, 0.05, 1.0);
	UpdateFont();
}

void ScalableLineEdit::resizeEvent(QResizeEvent* event)
{
	QLineEdit::resizeEvent(event);
	UpdateFont();
}

void ScalableLineEdit::changeEvent(QEvent* event)
{
	QLineEdit::changeEvent(event);

	if (event->type() == QEvent::StyleChange)
	{
		UpdateFont();
	}
}

void ScalableLineEdit::UpdateFont()
{
	const int pixel_size = std::max(10, static_cast<int>(height() * m_font_ratio));

	QFont current_font = font();
	if (current_font.pixelSize() == pixel_size)
	{
		return;
	}

	current_font.setPixelSize(pixel_size);
	setFont(current_font);
}
