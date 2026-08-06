#include "SettingsWidget.h"

namespace 
{
	constexpr double kPercentParentWidth = 0.25;
}

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent) 
{
	setAutoFillBackground(true);

	hide();
}

void SettingsWidget::Open() 
{
	if (m_is_open) 
	{
		return;
	}

	m_is_open = true;
	raise();
	const QRect closed(-width(), 0, width(), parentWidget()->height());
	const QRect opened(0, 0, width(), parentWidget()->height());

	setGeometry(closed);
	show();

	Animate(closed, opened);
}

void SettingsWidget::Close() 
{
	if (!m_is_open) 
	{
		return;
	}

	m_is_open = false;
	const QRect closed(-width(), 0, width(), parentWidget()->height());
	auto* anim = Animate(geometry(), closed);
	connect(anim, &QPropertyAnimation::finished, this, &SettingsWidget::hide);
}

void SettingsWidget::SyncHeight() 
{
	setGeometry(m_is_open ? 0 : -(parentWidget()->width() * kPercentParentWidth), 0, parentWidget()->width() * kPercentParentWidth, parentWidget()->height());
}

QPropertyAnimation* SettingsWidget::Animate(QRect from, QRect to) 
{
	auto* anim = new QPropertyAnimation(this, "geometry", this);
	anim->setDuration(200);
	anim->setStartValue(from);
	anim->setEndValue(to);
	anim->setEasingCurve(QEasingCurve::OutCubic);
	anim->start(QAbstractAnimation::DeleteWhenStopped);
	return anim;
}
