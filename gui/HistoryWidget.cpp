#include "HistoryWidget.h"

#include <QRect>
#include <QPropertyAnimation>
#include <QScrollArea>

namespace 
{
	constexpr int kHeight = 350;
}

HistoryWidget::HistoryWidget(QWidget* parent) : QWidget(parent)
{
	setFixedHeight(350);
	setAutoFillBackground(true);
	setAttribute(Qt::WA_StyledBackground, true);
	hide();

	QScrollArea* scroll_area = new QScrollArea;
	QWidget* buttons_container = new QWidget(this);
	scroll_area->setWidget(buttons_container);
	scroll_area->setWidgetResizable(true);
	scroll_area->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

void HistoryWidget::Open() 
{
	if (m_is_open) 
	{
		return;
	}

	m_is_open = true;
	raise();

	const QRect closed(0, parentWidget()->height(), parentWidget()->width(), kHeight);
	const QRect opened(0, parentWidget()->height() - kHeight, parentWidget()->width(), kHeight);

	setGeometry(closed);
	show();

	Animate(closed, opened);
}

void HistoryWidget::Close() 
{
	if (!m_is_open) 
	{
		return;
	}

	m_is_open = false;
	const QRect closed(0, parentWidget()->height(), parentWidget()->width(), kHeight);
	auto* anim = Animate(geometry(), closed);
	connect(anim, &QPropertyAnimation::finished, this, &HistoryWidget::hide);
}

void HistoryWidget::SyncWidth() 
{
	const auto parent_height = parentWidget()->height();

	setGeometry(0, m_is_open ? parent_height - kHeight : parent_height, parentWidget()->width(), kHeight);
}

bool HistoryWidget::IsOpen() const 
{
	return m_is_open;
}

QPropertyAnimation* HistoryWidget::Animate(QRect from, QRect to) 
{
	QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry", this);
	anim->setDuration(200);
	anim->setEasingCurve(QEasingCurve::OutCubic);
	anim->setStartValue(from);
	anim->setEndValue(to);
	anim->start(QAbstractAnimation::DeleteWhenStopped);

	return anim;
}
