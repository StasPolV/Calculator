#include "ScalableIconButton.h"

#include <QIcon>
#include <QResizeEvent>

#include <algorithm>

ScalableIconButton::ScalableIconButton(QWidget* parent) : QToolButton(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void ScalableIconButton::SetIconSource(QString path)
{
	m_source = QPixmap(path);
	m_icon_dirty = true;
	UpdateIcon();
}

void ScalableIconButton::SetIconRatio(double ratio)
{
	m_icon_ratio = std::clamp(ratio, 0.05, 1.0);
	UpdateIcon();
}

QSize ScalableIconButton::sizeHint() const
{
	return QSize(16, 16);
}

QSize ScalableIconButton::minimumSizeHint() const
{
	return QSize(0, 0);
}

void ScalableIconButton::resizeEvent(QResizeEvent* event)
{
	QToolButton::resizeEvent(event);
	UpdateIcon();
}

void ScalableIconButton::UpdateIcon()
{
	if (m_source.isNull())
	{
		return;
	}

	const int side = std::max(1, static_cast<int>(std::min(width(), height()) * m_icon_ratio));
	const QSize icon_size(side, side);

	if (!m_icon_dirty && iconSize() == icon_size && !icon().isNull())
	{
		return;
	}

	const qreal dpr = devicePixelRatioF();
	QPixmap scaled =
	        m_source.scaled(icon_size * dpr, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	scaled.setDevicePixelRatio(dpr);

	setIconSize(icon_size);
	setIcon(QIcon(scaled));
	m_icon_dirty = false;
}
