#include "HistoryWidget.h"

#include "ScalableButton.h"

#include <QPropertyAnimation>
#include <QRect>
#include <QScrollArea>
#include <QVBoxLayout>

namespace
{
	constexpr int kHeight = 400;
}

HistoryWidget::HistoryWidget(QWidget* parent) : QWidget(parent)
{
	setFixedHeight(kHeight);
	setAutoFillBackground(true);
	setAttribute(Qt::WA_StyledBackground, true);
	hide();

	QVBoxLayout* main_layout = new QVBoxLayout(this);

	QScrollArea* scroll_area = new QScrollArea;
	m_buttons_container = new QWidget(this);
	m_container_layout = new QVBoxLayout(m_buttons_container);

	scroll_area->setWidget(m_buttons_container);
	scroll_area->setWidgetResizable(true);
	scroll_area->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	main_layout->addWidget(scroll_area);
}

void HistoryWidget::AddHistory(QString full_expression)
{
	ScalableButton* history_button = new ScalableButton(full_expression, this);
	history_button->setFixedHeight(60);
	history_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	history_button->SetFontRatio(0.5);

	m_container_layout->addWidget(history_button);
	m_container_layout->setAlignment(Qt::AlignTop);

	connect(history_button, &ScalableButton::clicked, this,
	        [this, full_expression]()
	        {
		        const qsizetype index = full_expression.indexOf("= ");
		        const QString result = full_expression.mid(index + 2);
		        emit HistoryButtonClicked(result);
	        });
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

	setMaximumWidth(parentWidget()->width());

	setGeometry(0, m_is_open ? parent_height - kHeight : parent_height, parentWidget()->width(),
	            kHeight);
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
